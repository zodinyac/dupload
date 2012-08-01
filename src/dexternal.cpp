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

#include "dexternal.h"

dExternal::dExternal( dUpload *d ) : m_dupload( d )
{
	m_netman = new QNetworkAccessManager();
	connect( m_netman, SIGNAL( finished( QNetworkReply * ) ), this, SLOT( finished( QNetworkReply * ) ) );

	timerShot();

	get( "hello.php" );
	get( "new.php" );
}

dExternal::~dExternal()
{
}

dExternal *dExternal::instance( dUpload *d )
{
	static dExternal *me = new dExternal( d );

	return me;
}

void dExternal::userRegister()
{
	get( "register.php" );
}

void dExternal::get( const QString &w, const QString &p )
{
	m_netman->get( QNetworkRequest ( QUrl( "http://u.deltaz.org/" + w + "?i=" + m_dupload->getUserLogin() + ( p.isEmpty() ? "" : "&" ) + p ) ) );
}

void dExternal::userAuth()
{
	m_passkey = QInputDialog::getText( m_dupload, "Passkey", "Enter your passkey", QLineEdit::Password );
	if ( m_passkey.isEmpty() )
		return;
	
	get( "auth.php", "v=" + m_passkey );
}

void dExternal::finished( QNetworkReply *reply )
{
	while( reply->bytesAvailable() )
	{
		QString r = QTextCodec::codecForLocale()->toUnicode( reply->readLine() );
		r.remove( "\n" );

		if ( r.startsWith( "I:" ) )
		{
			if ( r.section( ':', 1, 1 ) == "1" )
			{
				QString passkey = QInputDialog::getText( m_dupload, "Passkey", "Enter your new passkey and remember. Length of this is from 5 to 32 symbols.", QLineEdit::Password );
				get( "set.php", "t=1&v=" + passkey );
			}
			else if ( r.section( ':', 1, 1 ) == "2" )
				QMessageBox::information( m_dupload, "", "You're already registered" );
			else if ( r.section( ':', 1, 1 ) == "3" )
				QMessageBox::warning( m_dupload, "", "Incorrect passkey" );
		}
		else if ( r.startsWith( "M:" ) )
		{
			r.remove( 0, 2 );
			QMessageBox::warning( m_dupload, "", r );
		}
		else if ( r.startsWith( "N:" ) )
		{
			r.remove( 0, 2 );
			r.replace( "|", "\n" );
			if ( r != "0" )
				m_dupload->notify( r );

			QTimer::singleShot( 5 * 60 * 1000, this, SLOT( timerShot() ) ); // 5 mins
		}
		else if ( r.startsWith( "U:" ) )
		{
			r.remove( 0, 2 );
			m_dupload->setPasskey( m_passkey );
			m_dupload->setUserlogin( r );
			m_dupload->notify( "You're logged in as " + r );
		}
	}

	reply->deleteLater();
}

void dExternal::timerShot()
{
	get( "new.php" );
}
