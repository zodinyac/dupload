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

dTrayIcon::dTrayIcon( dUpload *d ) : m_dupload( d )
{
	connect( this, SIGNAL( activated( QSystemTrayIcon::ActivationReason ) ), this, SLOT( activated( QSystemTrayIcon::ActivationReason ) ) );
	connect( this, SIGNAL( messageClicked() ), this, SLOT( messageClicked() ) );
	connect( &m_menu, SIGNAL( triggered( QAction * ) ), this, SLOT( menuTriggered( QAction * ) ) );

	m_menu.addAction( m_dupload->windowIcon(), "Send as JPG" )->setData( 0 );
	m_menu.addAction( m_dupload->windowIcon(), "Send as PNG" )->setData( 1 );
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
		{
			m_dupload->show();
			m_dupload->activateWindow();
		}
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
		showMessage( "Screenshot was successfully loaded", "Click here for copy link to clipboard\n" + m_link );
	}
	else if ( type == 1 && !m_dupload->isVisible() )
		showMessage( "Loading...", s, QSystemTrayIcon::NoIcon );
	else if ( type == 2 )
		showMessage( "Error", s, QSystemTrayIcon::Critical );
}

void dTrayIcon::menuTriggered( QAction *a )
{
	m_dupload->sendFromClipboard( a->data().toInt() );
}
