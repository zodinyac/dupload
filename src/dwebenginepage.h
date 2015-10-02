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

#ifndef DWEBENGINEVIEWPAGE_H
#define DWEBENGINEVIEWPAGE_H

#include <QtWebEngineWidgets/QWebEnginePage>

class dWebEnginePage : public QWebEnginePage
{
	Q_OBJECT

public:
	dWebEnginePage( QObject *parent = 0 );
	~dWebEnginePage();

signals:
	void linkClicked( const QUrl &url );

protected:
	bool acceptNavigationRequest( const QUrl &url, NavigationType type, bool isMainFrame = 0 );
};

#endif // DWEBENGINEVIEWPAGE_H
