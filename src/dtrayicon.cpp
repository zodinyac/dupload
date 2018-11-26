/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2009-2010 by Belov Nikita <null@deltaz.org>
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

#include "dtrayicon.h"
#include "dgallery.h"

#if defined ( Q_WS_MAC )
	void qt_mac_set_dock_menu( QMenu *menu );
#endif

dTrayIcon::dTrayIcon( dUpload *d ) : m_dupload( d )
{
	connect( this, SIGNAL( activated( QSystemTrayIcon::ActivationReason ) ), this, SLOT( activated( QSystemTrayIcon::ActivationReason ) ) );
	connect( this, SIGNAL( messageClicked() ), this, SLOT( messageClicked() ) );
	connect( &m_menu, SIGNAL( triggered( QAction * ) ), this, SLOT( menuTriggered( QAction * ) ) );

	m_menu.addAction( m_dupload->windowIcon(), "Send as JPG" )->setData( 0 );
	m_menu.addAction( m_dupload->windowIcon(), "Send as PNG" )->setData( 1 );
	m_menu.addAction( m_dupload->windowIcon(), "Last 10 images" )->setData( 3 );

#if defined ( Q_WS_MAC ) || defined ( Q_WS_X11 )
	m_menu.addSeparator();
	m_menu.addAction( m_dupload->windowIcon(), "Show / Hide" )->setData( 2 );

	#if !defined ( Q_WS_X11 )
		qt_mac_set_dock_menu( &m_menu );
	#endif
#endif

	setContextMenu( &m_menu );

	setIcon( m_dupload->windowIcon() );
	show();
}

dTrayIcon::~dTrayIcon()
{
	hide();
}

void dTrayIcon::activated( QSystemTrayIcon::ActivationReason r )
{
	if ( r == QSystemTrayIcon::DoubleClick )
	{
		if ( m_dupload->isVisible() )
			m_dupload->hide();
		else
			m_dupload->show();
	}
}

void dTrayIcon::messageClicked()
{
	if ( !m_link.isEmpty() )
	{
		QApplication::clipboard()->setText( m_link );
		m_link.clear();
	}
}

void dTrayIcon::message( const QString &s, int type )
{
	if ( type == 0 )
	{
		m_link = s;
		showMessage( "Screenshot was successfully uploaded", "Click here for copy link to clipboard\n" + m_link );
	}
	else if ( type == 1 && !m_dupload->isVisible() )
		showMessage( "Loading...", s, QSystemTrayIcon::NoIcon );
	else if ( type == 2 )
		showMessage( "Error", s, QSystemTrayIcon::Critical );
	else if ( type == 3 )
		showMessage( "Information", s, QSystemTrayIcon::Information );
}

void dTrayIcon::updateToolTip()
{
	QString toolTipLogged = ( m_dupload->passkey().isEmpty() ? QString() : "logged in as " );
	QString toolTip = "You're " + toolTipLogged + m_dupload->userlogin();

	setToolTip( toolTip );
}

void dTrayIcon::menuTriggered( QAction *a )
{
#if defined ( Q_WS_MAC ) || defined ( Q_WS_X11 )
	if ( a->data().toInt() == 2 ) {
		activated( QSystemTrayIcon::DoubleClick );
		return;
	}
#endif
	if ( a->data().toInt() == 3 )
		m_dupload->showLast();
	else
		m_dupload->sendFromClipboard( a->data().toInt() );
}
