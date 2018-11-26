/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2015 by Belov Nikita <zodiac.nv@gmail.com>
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

#include "ddesktopmanager.h"
#include "dsettings.h"

#include <QtGui/QCursor>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

dDesktopManager::dDesktopManager()
{
}

dDesktopManager::~dDesktopManager()
{
}

dDesktopManager *dDesktopManager::instance()
{
	static dDesktopManager *me = new dDesktopManager();
	return me;
}

QScreen *dDesktopManager::cursorScreen()
{
	QPoint globalCursorPos = QCursor::pos();
	int screenNumber = QApplication::desktop()->screenNumber( globalCursorPos );

	return QGuiApplication::screens().at( screenNumber );
}

QScreen *dDesktopManager::selectScreen()
{
	QScreen *screen = nullptr;

	m_selectDialog = new QDialog();
	m_selectDialog->setAttribute( Qt::WA_DeleteOnClose );
	m_selectDialog->setAttribute( Qt::WA_QuitOnClose, false );
	m_selectDialog->setWindowFlags( m_selectDialog->windowFlags() ^ Qt::WindowContextHelpButtonHint | Qt::MSWindowsFixedSizeDialogHint );

	select_ui.setupUi( m_selectDialog );

	for ( int i = 0; i < QGuiApplication::screens().count(); i++ )
	{
		QString name = QGuiApplication::screens().at( i )->name();
		if ( QGuiApplication::screens().at( i ) == QGuiApplication::primaryScreen() )
		{
			name += " (primary)";
		}

		auto commandLinkButton = new QCommandLinkButton( name );
		commandLinkButton->setProperty( "screen", i );

		connect( commandLinkButton, &QCommandLinkButton::clicked, [&, commandLinkButton]( bool )
		{
			int screenNumber = commandLinkButton->property( "screen" ).toInt();
			screen = QGuiApplication::screens().at( screenNumber );
			m_selectDialog->done( QDialog::Accepted );

			// ugly hack to prevent to screenshot that dialog
			QThread::msleep( 300 );
		}
		);

		select_ui.verticalLayout->addWidget( commandLinkButton );
	}

	m_selectDialog->exec();
	m_selectDialog = nullptr;

	return screen;
}

QScreen *dDesktopManager::getPrimaryScreen()
{
	int source = dSettings::instance()->get< int >( "screen_src", dDesktopManager::DDM_PRIMARY );
	QScreen *screen = QApplication::primaryScreen();

	if ( source == dDesktopManager::DDM_CURSOR )
	{
		screen = cursorScreen();
	}
	else
	{
		screen = QApplication::primaryScreen();
	}

	return screen;
}

QScreen *dDesktopManager::getPrimaryScreenAS()
{
	int source_as = dSettings::instance()->get< int >( "screen_as", dDesktopManager::DDM_PRIMARY );
	QScreen *screen = QApplication::primaryScreen();

	if ( source_as == dDesktopManager::DDM_CURSOR )
	{
		screen = cursorScreen();
	}
	else if ( source_as == dDesktopManager::DDM_ASK )
	{
		screen = selectScreen();
	}
	else
	{
		screen = QApplication::primaryScreen();
	}

	return screen;
}

QPoint dDesktopManager::getScreenCoord( QScreen *screen )
{
	return screen->geometry().topLeft();
}

QPixmap dDesktopManager::makeScreenshot()
{
	int source = dSettings::instance()->get< int >( "screen_src", dDesktopManager::DDM_PRIMARY );
	QScreen *screen = QApplication::primaryScreen();

	if ( source == dDesktopManager::DDM_PRIMARY )
	{
		screen = QApplication::primaryScreen();
	}
	else if ( source == dDesktopManager::DDM_CURSOR )
	{
		screen = cursorScreen();
	}
	else if ( source == dDesktopManager::DDM_ASK )
	{
		screen = selectScreen();
		if ( screen == nullptr )
		{
			return QPixmap();
		}
	}
	else if ( source == dDesktopManager::DDM_CONCAT )
	{
		int width = 0;
		int height = 0;
		for ( QScreen *cur_screen : QGuiApplication::screens() )
		{
			if ( cur_screen->geometry().height() > height )
			{
				height = cur_screen->geometry().height();
			}
			width += cur_screen->geometry().width();
		}

		QPixmap screenshot( width, height );
		screenshot.fill( Qt::black );

		int cur_width = 0;
		QPainter painter( &screenshot );
		for ( QScreen *cur_screen : QGuiApplication::screens() )
		{
			QRect g = cur_screen->geometry();
			QPixmap cur_screenshot = cur_screen->grabWindow( 0, g.x(), g.y(), g.width(), g.height() );
			painter.drawPixmap( cur_width, 0, g.width(), g.height(), cur_screenshot );

			cur_width += g.width();
		}
		painter.end();

		return screenshot;
	}
	else
	{
		return QPixmap();
	}

	return makeScreenshot (screen );
}

QPixmap dDesktopManager::makeScreenshot( QScreen *screen )
{
	QRect g = screen->geometry();
	QPixmap screenshot = screen->grabWindow( 0 );

	if ( m_selectDialog )
	{
		m_selectDialog->close();
		m_selectDialog->deleteLater();
		m_selectDialog = nullptr;
	}

	return screenshot;
}
