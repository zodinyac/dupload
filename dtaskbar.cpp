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

#include "dtaskbar.h"

#if defined( DTASKBARACTIVE )

dTaskBar::dTaskBar()
{
	m_taskbarlist = 0;
	init();
}

dTaskBar::~dTaskBar()
{
	m_taskbarlist->Release();
	m_taskbarlist = 0;
}

dTaskBar *dTaskBar::instance()
{
	static dTaskBar *me = new dTaskBar;

	return me;
}

bool dTaskBar::init()
{
	if ( m_taskbarlist )
		return 0;

	HRESULT hr = CoCreateInstance( CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &m_taskbarlist ) );
	if ( FAILED( hr ) )
		return 0;

	hr = m_taskbarlist->HrInit();
	if ( FAILED( hr ) )
	{
		m_taskbarlist->Release();
		m_taskbarlist = 0;

		return 0;
	}

	return 1;
}

void dTaskBar::setProgressState( HWND wid, int state )
{
	if ( !m_taskbarlist )
		return;

	TBPFLAG flag;
	if ( state == 0 )
		flag = TBPF_NOPROGRESS;
	else if ( state == 1 )
		flag = TBPF_NORMAL;

	m_taskbarlist->SetProgressState( wid, flag );
}

void dTaskBar::setProgressValue( HWND wid, qint64 received, qint64 total )
{
	if ( !m_taskbarlist )
		return;

	m_taskbarlist->SetProgressValue( wid, received, total );
}

#endif // DTASKBARACTIVE
