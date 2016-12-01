/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2012, 2015 by Belov Nikita <null@deltaz.org>
 *
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************
*****************************************************************************/

#ifdef Q_OS_WIN
#include <QtWinExtras>
#include "shobjidl.h"
#endif

#include "dwebcam.h"

QByteArray dWebCam::m_defaultDevice = QByteArray(); 

dWebCam::dWebCam( dUpload *d ) : m_dupload( d )
{
	ui.setupUi( this );
	setAttribute( Qt::WA_DeleteOnClose );
	setAttribute( Qt::WA_QuitOnClose, false );

	aeroBackground();

	QList< QByteArray > cams = QCamera::availableDevices();
	if ( !cams.contains( m_defaultDevice ) )
	{
		if ( cams.count() == 0 )
		{
			QMessageBox::critical( this, "Error", "Web Cams are not found!" );

			deleteLater();
			return;
		}
		else if ( cams.count() == 1 )
		{
			m_defaultDevice = cams.at( 0 );
		}
		else
		{
			m_selectDialog = new QDialog();
			m_selectDialog->setAttribute( Qt::WA_DeleteOnClose );
			m_selectDialog->setAttribute( Qt::WA_QuitOnClose, false );
			m_selectDialog->setWindowFlags( m_selectDialog->windowFlags() ^ Qt::WindowContextHelpButtonHint | Qt::MSWindowsFixedSizeDialogHint );

			select_ui.setupUi( m_selectDialog );

			foreach( QByteArray webCam, cams )
			{
				auto commandLinkButton = new QCommandLinkButton( QCamera::deviceDescription( webCam ) );
				commandLinkButton->setProperty( "webCam", webCam );

				connect( commandLinkButton, &QCommandLinkButton::clicked, [=]( bool )
					{
						m_defaultDevice = commandLinkButton->property( "webCam" ).toByteArray();
						m_selectDialog->accept();
					}
				);

				select_ui.verticalLayout->addWidget( commandLinkButton );
			}

			if ( m_selectDialog->exec() == QDialog::Rejected )
			{
				deleteLater();
				return;
			}
		}
	}

	m_camera = new QCamera( m_defaultDevice );
	connect( m_camera, SIGNAL( error( QCamera::Error ) ), this, SLOT( cameraError( QCamera::Error ) ) );
	connect( m_camera, SIGNAL( stateChanged( QCamera::State ) ), this, SLOT ( cameraStateChanged( QCamera::State ) ) );

	auto viewfinder = new QCameraViewfinder;
	viewfinder->setMinimumSize( 50, 50 );

	m_camera->setViewfinder( viewfinder );
	m_camera->setCaptureMode( QCamera::CaptureStillImage );

	auto timerLabel = new QLabel;
	QString timerLabelTpl = "<p align=\"center\"><span style=\"font-size:50pt; font-weight:600; color:#FF0000;\">%1</span></p>";
	
	timerLabel->hide();
	ui.picture->hide();
	ui.uploadAsJpgButton->hide();
	ui.openInHighlighterButton->hide();
	ui.recaptureButton->hide();

	ui.captureButton->setDisabled( true );
	ui.timerButton->setDisabled( true );

	ui.gridLayout_3->addWidget( viewfinder, 0, 0 );
	ui.gridLayout_3->addWidget( timerLabel, 0, 0 );

	m_timerPaintState = 0;

	m_timer = new QTimer( this );
	m_timer->setInterval( 1000 );

	connect( m_timer, &QTimer::timeout, [=]()
		{
			m_timerPaintState--;

			if ( m_timerPaintState )
			{
				timerLabel->setText( timerLabelTpl.arg( QString::number( m_timerPaintState ) ) );
			}
			else
			{
				m_timer->stop();
				timerLabel->hide();

				capture();
			}
		}
	);

	connect( ui.captureButton, &QPushButton::clicked, this, &dWebCam::capture );
	connect( ui.timerButton, &QPushButton::clicked, [=]( bool )
		{
			ui.captureButton->setDisabled( true );
			ui.timerButton->setDisabled( true );

			m_timerPaintState = 3;
			m_timer->start();

			timerLabel->show();
			timerLabel->setText( timerLabelTpl.arg( QString::number( m_timerPaintState ) ) );
		}
	);

	connect( ui.uploadAsJpgButton, &QPushButton::clicked, [=]( bool )
		{
			QApplication::clipboard()->setImage( m_pixmap.toImage() );
			m_dupload->sendFromClipboard();
			close();
		}
	);
	connect( ui.openInHighlighterButton, &QPushButton::clicked, [=]( bool )
		{
			QApplication::clipboard()->setImage( m_pixmap.toImage() );
			new dHighlighter( m_dupload );
			close();
		}
	);
	connect( ui.recaptureButton, &QPushButton::clicked, [=]( bool )
		{
			ui.picture->hide();
			ui.uploadAsJpgButton->hide();
			ui.openInHighlighterButton->hide();
			ui.recaptureButton->hide();
			
			viewfinder->show();
			ui.captureButton->show();
			ui.timerButton->show();
		}
	);

	show();

	activateWindow();
	raise();

	m_camera->start();

	m_imageCapture = new QCameraImageCapture( m_camera );
//	m_imageCapture->setCaptureDestination( QCameraImageCapture::CaptureToBuffer );
	m_imageCapture->setCaptureDestination( QCameraImageCapture::CaptureToFile );

	{
		QList<QVideoFrame::PixelFormat> formats = m_imageCapture->supportedBufferFormats();
		qDebug() << "formats" << formats;

		QList<QSize> resolutions = m_imageCapture->supportedResolutions();
		qDebug() << "resolutions" << resolutions;

		QStringList codecs = m_imageCapture->supportedImageCodecs();
		qDebug() << "codecs" << codecs;
	}

	connect( m_imageCapture, &QCameraImageCapture::imageCaptured, [=]( int id, const QImage &image )
		{
			qDebug() << id << "captured";

			viewfinder->hide();
			ui.captureButton->hide();
			ui.timerButton->hide();

			ui.uploadAsJpgButton->show();
			ui.openInHighlighterButton->show();
			ui.recaptureButton->show();

			m_pixmap = QPixmap::fromImage( image.mirrored( true, false ) );

			ui.picture->setPixmap( m_pixmap.scaled( ui.picture->width(), ui.picture->height(), Qt::KeepAspectRatio ) );
			ui.picture->show();
		}
	);

	connect( m_imageCapture, &QCameraImageCapture::imageSaved, [=]( int id, const QString &fileName )
		{
			qDebug() << id << "saved" << fileName;

			QFile imageFile( fileName );
			
			if ( imageFile.exists() )
			{
				m_pixmap = QPixmap::fromImage( QImage( fileName ).mirrored( true, false ) );
				ui.picture->setPixmap( m_pixmap.scaled( ui.picture->width(), ui.picture->height(), Qt::KeepAspectRatio ) );
				imageFile.remove();
			}
			else
			{
				QMessageBox::critical( this, "Error", "Image file are not found!" );

				deleteLater();
				return;
			}
		}
	);

	qDebug() << "viewfinder size:" << viewfinder->width() << "x" << viewfinder->height();
}

dWebCam::~dWebCam()
{
	if ( m_camera )
	{
		m_camera->stop();
		m_camera->deleteLater();
	}

	if ( m_imageCapture )
	{
		m_imageCapture->deleteLater();
	}
}

void dWebCam::capture( bool )
{
	m_camera->searchAndLock();
	m_imageCapture->capture( QCoreApplication::applicationDirPath() + "/image.jpg" );
	m_camera->unlock();

	ui.captureButton->setEnabled( true );
	ui.timerButton->setEnabled( true );
}

void dWebCam::cameraError( QCamera::Error value )
{
	QMessageBox::critical( this, "Error", m_camera->errorString() );

	deleteLater();
}

void dWebCam::cameraStateChanged( QCamera::State state )
{
	ui.captureButton->setEnabled( state == QCamera::ActiveState );
	ui.timerButton->setEnabled( state == QCamera::ActiveState );
}

void dWebCam::aeroBackground()
{
#ifdef Q_OS_WIN
	if ( QtWin::isCompositionEnabled() )
	{
		QtWin::extendFrameIntoClientArea( this, -1, -1, -1, -1 );
		setAttribute( Qt::WA_TranslucentBackground, true );
		setAttribute( Qt::WA_NoSystemBackground, false );
		setStyleSheet( "dWebCam { background: transparent; }" );
	}
	else
	{
		QtWin::resetExtendedFrame( this );
		setAttribute( Qt::WA_TranslucentBackground, false );
		setStyleSheet( QString( "dWebCam { background: %1; }" ).arg( QtWin::realColorizationColor().name() ) );
	}
#endif
}

bool dWebCam::event( QEvent *event )
{
#ifdef Q_OS_WIN
	if ( event->type() == QWinEvent::CompositionChange || event->type() == QWinEvent::ColorizationChange )
	{
		aeroBackground();
	}
#endif

	return QWidget::event( event );
}

void dWebCam::mousePressEvent( QMouseEvent *event )
{
	if( event->button() == Qt::LeftButton )
		m_drag_pos = event->globalPos() - frameGeometry().topLeft();
}

void dWebCam::mouseMoveEvent( QMouseEvent *event )
{
	if( event->buttons() & Qt::LeftButton )
		move( event->globalPos() - m_drag_pos );
}

void dWebCam::paintEvent( QPaintEvent *event )
{

#ifdef Q_OS_WIN
	if ( QtWin::isCompositionEnabled() )
	{
		QPainter p( this );
		p.setCompositionMode( QPainter::CompositionMode_Clear );
		p.fillRect( 0, 0, width(), height(), QColor() );
	}
#endif
}

void dWebCam::resizeEvent( QResizeEvent *event )
{
	ui.picture->setPixmap( m_pixmap.scaled( ui.picture->width(), ui.picture->height(), Qt::KeepAspectRatio ) );
}
