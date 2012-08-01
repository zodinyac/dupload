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

#ifndef DTASKBAR_H
#define DTASKBAR_H

#include "dupload.h"

#if defined( Q_OS_WIN )

#include <windows.h>

#if (WINVER >= 0x0601)
#define DTASKBARACTIVE

#include <shobjidl.h>

class dTaskBar
{
public:
	dTaskBar();
	~dTaskBar();
	static dTaskBar *instance();

	void setProgressState( HWND wid, int state = 0 );
	void setProgressValue( HWND wid, qint64 received = 0, qint64 total = 0 );

private:
	bool init();

	ITaskbarList3 *m_taskbarlist;
};

#endif // WINVER >= 0x0601
#endif // Q_OS_WIN
#endif // DTASKBAR_H
