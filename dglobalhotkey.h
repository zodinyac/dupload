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

#ifndef DGLOBALHOTKEY_H
#define DGLOBALHOTKEY_H

#include <QObject>
#include <QAbstractEventDispatcher>
#include <QKeySequence>
#include <QMap>
#include <QHash>

#if defined( Q_WS_WIN )
	#include <windows.h>
#elif defined( Q_WS_X11 )
	#include <QX11Info>
	#include <X11/Xlib.h>
#elif defined( Q_WS_MAC )
	#include <Carbon/Carbon.h>
#endif

class dGlobalHotKey : public QObject
{
	Q_OBJECT

public:
	dGlobalHotKey();
	~dGlobalHotKey();

	static bool eventFilter( void *e );
	static dGlobalHotKey *instance();

	bool shortcut( const QString &s, bool a = true );
	quint32 id( const QString &s );

	void native( const QString &s, quint32 &k, quint32 &m );

	#if defined( Q_WS_X11 )
		bool error;
	#endif

signals:
	void hotKeyPressed( quint32 k );

private:
	quint32 nativeModifiers( Qt::KeyboardModifiers m );
	quint32 nativeKeycode( Qt::Key k );
};

#endif // DGLOBALHOTKEY_H