/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2013 by Belov Nikita <null@deltaz.org>
 *
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                  m_dll                                                       *
 ***************************************************************************
*****************************************************************************/

#ifdef Q_OS_WIN
#include "ddll.h"
#include "dSettings.h"

dDll::dDll()
{
	m_dUploadDll.setFileName( "dUploadDll32.dll" );

	if ( m_dUploadDll.load() )
	{
		hookInstall = ( pHookInstall )m_dUploadDll.resolve( "hookInstall" );
		hookUninstall = ( pHookUninstall )m_dUploadDll.resolve( "hookUninstall" );

		addWatchingApp = ( pAddWatchingApp )m_dUploadDll.resolve( "addWatchingApp" );
		clearWatchingApps = ( pClearWatchingApps )m_dUploadDll.resolve( "clearWatchingApps" );

		setHWND = ( pSetHWND )m_dUploadDll.resolve( "setHWND" );

		updateSettings();

		hookInstall();
	}
}

dDll::~dDll()
{
	if ( m_dUploadDll.isLoaded() )
		hookUninstall();
}

void dDll::changeHWND( HWND hwnd )
{
	m_hwnd = hwnd;

	if ( m_dUploadDll.isLoaded() )
		setHWND( m_hwnd );
}

void dDll::updateSettings()
{
	if ( !m_dUploadDll.isLoaded() )
		return;

	clearWatchingApps();

	QStringList apps = dSettings::instance()->get< QString >( "MPNames" ).split( ",", QString::SkipEmptyParts );
	Q_FOREACH( const QString &app, apps )
	{
		addWatchingApp( app.toStdWString().c_str() );
	}
}
#endif
