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

#include "dlast.h"

dWebEnginePage::dWebEnginePage( QObject *parent ) : QWebEnginePage( parent )
{
}

dWebEnginePage::~dWebEnginePage()
{
}

bool dWebEnginePage::acceptNavigationRequest( const QUrl &url, NavigationType type, bool isMainFrame )
{
	if ( type == QWebEnginePage::NavigationTypeLinkClicked )
	{
		emit linkClicked( url );
		return false;
	}
	else
	{
		return true;
	}
}
