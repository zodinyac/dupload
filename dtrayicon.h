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

#ifndef DTRAYICON_H
#define DTRAYICON_H

#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include "dupload.h"

class dUpload;

class dTrayIcon : public QSystemTrayIcon
{
	Q_OBJECT

public:
	dTrayIcon( dUpload *d );
	~dTrayIcon();

	void message( const QString &s, int type = 0 );

public slots:
	void activated( QSystemTrayIcon::ActivationReason r );
	void messageClicked();
	void menuTriggered( QAction *a );

private:
	dUpload *m_dupload;

	QString m_link;

	QMenu m_menu;
};

#endif // DTRAYICON_H
