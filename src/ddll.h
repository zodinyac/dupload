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
 *                                                                         *
 ***************************************************************************
*****************************************************************************/

#ifndef DDLL_H
#define DDLL_H

#define NOMINMAX
#include <windows.h>

#include <QtCore/QLibrary>

typedef void ( *pHookInstall )( void ); 
typedef void ( *pHookUninstall )( void );

typedef void ( *pAddWatchingApp )( const wchar_t * );
typedef void ( *pClearWatchingApps )( void );

typedef void ( *pSetHWND )( HWND );

class dDll : public QObject
{
	Q_OBJECT

public:
	dDll();
	~dDll();

	void changeHWND( HWND hwnd );

	void updateSettings();

private:
	pHookInstall hookInstall;
	pHookUninstall hookUninstall;

	pAddWatchingApp addWatchingApp;
	pClearWatchingApps clearWatchingApps;

	pSetHWND setHWND;

	QLibrary m_dUploadDll;
	HWND m_hwnd;
};

#endif // DDLL_H
