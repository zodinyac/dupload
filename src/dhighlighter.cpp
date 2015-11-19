/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2010, 2012-2013, 2015 by Belov Nikita <null@deltaz.org>
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

#include <QtGui/QPainterPath>

#include "ddesktopmanager.h"
#include "dhighlighter.h"
#include "dsettings.h"

dHighlighter::dHighlighter( dUpload *d ) : m_dupload( d )
{
	ui.setupUi( this );
	setAttribute( Qt::WA_DeleteOnClose );
	setAttribute( Qt::WA_QuitOnClose, false );

	QPixmap pixmap = QPixmap::fromImage( QApplication::clipboard()->image() );

	if ( pixmap.isNull() && QApplication::clipboard()->mimeData()->hasUrls() )
		pixmap.load( QApplication::clipboard()->mimeData()->urls()[0].toLocalFile() );

	if ( pixmap.isNull() )
	{
		pixmap = dDesktopManager::instance()->makeScreenshot();
	}

	if ( pixmap.isNull() )
	{
		close();
		return;
	}

	ui.image->setPixmap( pixmap );
	
	m_lastPos = QPoint( -1, -1 );

	QPoint window_pos = dDesktopManager::instance()->getScreenCoord( dDesktopManager::instance()->getPrimaryScreen() );
	move( window_pos );
	showMaximized();

	#if defined( Q_WS_X11 )
		XClientMessageEvent xev;
		xev.type = ClientMessage;
		xev.window = winId();
		xev.message_type = XInternAtom( QX11Info::display(), "_NET_ACTIVE_WINDOW", False );
		xev.format = 32;
		xev.data.l[0] = 2;
		xev.data.l[1] = QX11Info::appUserTime();

		XSendEvent( QX11Info::display(), QX11Info::appRootWindow(), False, ( SubstructureNotifyMask | SubstructureRedirectMask ), ( XEvent * ) &xev );
	#else
		activateWindow();
		raise();
	#endif
}

dHighlighter::~dHighlighter()
{
}

void dHighlighter::keyPressEvent( QKeyEvent *event )
{
#if defined( Q_WS_WIN ) || defined( Q_WS_MAC )
	quint32 key = event->nativeVirtualKey();
#elif defined( Q_WS_X11 )
	quint32 key = event->nativeScanCode();
#endif

	if ( m_lastPos != QPoint( -1, -1 ) )
		return;

	if ( key == m_dupload->nativeKeycode( 'B' ) )
	{
		QApplication::clipboard()->setImage( ui.image->pixmap().toImage() );
		m_dupload->sendFromClipboard();
		close();
	}
	else if ( key == m_dupload->nativeKeycode( 'N' ) )
	{
		QApplication::clipboard()->setImage( ui.image->pixmap().toImage() );
		m_dupload->sendFromClipboard( 1 );
		close();
	}
	else if ( key == m_dupload->nativeKeycode( 'Z' ) )
	{
		ui.image->undo();
	}
	else if ( key == m_dupload->nativeKeycode( 'C' ) )
	{
		QApplication::clipboard()->setImage( ui.image->pixmap().toImage() );
		close();
	}
	else if ( key == m_dupload->nativeKeycode( 'S' ) )
	{
		dSettings::instance()->show( 2 ); // for highlighter settings tab
	}
	else if ( event->key() == Qt::Key_Escape )
	{
		close();
	}
}

void dHighlighter::mousePressEvent( QMouseEvent *event )
{
	dSettings *settings = dSettings::instance();

	QColor color;
	qreal opacity;
	qreal width;

	if ( event->button() == Qt::LeftButton )
	{
		color = settings->get< QColor >( "highlighterLeftButtonColor", Qt::red );
		opacity = settings->get( "highlighterLeftButtonOpacity", 1.0 );
		width = settings->get( "highlighterLeftButtonWidth", 4.0 );
	}
	else
	{
		color = settings->get< QColor >( "highlighterRightButtonColor", Qt::yellow );
		opacity = settings->get< qreal >( "highlighterRightButtonOpacity", 0.3 );
		width = settings->get( "highlighterRightButtonWidth", 20.0 );
	}

	ui.image->setOpacity( opacity );
	ui.image->setPen( QPen( color, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );

	m_lastPos = event->pos();
	m_path = QPainterPath( m_lastPos + scrollBarShift() );

	m_pathPrev = QPainterPath();
	m_pathFlag = PATH_FIRST;
}

void dHighlighter::mouseMoveEvent( QMouseEvent *event )
{
	if( !( event->buttons() & Qt::LeftButton || event->buttons() & Qt::RightButton ) || m_lastPos == QPoint( -1, -1 ) )
		return;

	if ( m_pathFlag != PATH_FIRST )
	{
		m_pathPrev = m_path;
		m_pathFlag = PATH_OK;
	}
	else
	{
		m_pathFlag = PATH_SECOND;
	}

	if ( m_pathFlag == PATH_OK )
	{
		ui.image->drawPath( m_pathPrev );
		m_path = QPainterPath( m_pathPrev.currentPosition() );
	}

	m_path.quadTo( m_lastPos + scrollBarShift(), ( m_lastPos + event->pos() ) / 2 + scrollBarShift() );
	
	ui.image->drawPath( m_path );

	m_lastPos = event->pos();
}

void dHighlighter::mouseReleaseEvent( QMouseEvent * /*event*/ )
{
	if ( m_lastPos == QPoint( -1, -1 ) )
		return;

	if ( m_path.isEmpty() )
		ui.image->drawPoint( m_lastPos + scrollBarShift() );
	else
		ui.image->drawPath( m_path, true );

	m_lastPos = QPoint( -1, -1 );
}

void dHighlighter::tabletEvent( QTabletEvent *event )
{
	qDebug() << event->device() << event->globalPos() << event->pos() << event->pressure() << event->rotation() << event->tangentialPressure();
	event->accept();
}

QPoint dHighlighter::scrollBarShift()
{
	return QPoint( ui.scrollArea->horizontalScrollBar()->value(), ui.scrollArea->verticalScrollBar()->value() );
}
