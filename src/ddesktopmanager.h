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

#ifndef DDESKTOPMANAGER_H
#define DDESKTOPMANAGER_H

#include <QtCore/QtCore>

#include "ui_dscreenselect.h"

class dDesktopManager : public QObject
{
	Q_OBJECT

public:
	enum
	{
		DDM_PRIMARY,
		DDM_CURSOR,
		DDM_ASK,
		DDM_CONCAT
	};

	~dDesktopManager();

	static dDesktopManager *instance();

	QScreen *getPrimaryScreen();
	QScreen *getPrimaryScreenAS();

	QPoint getScreenCoord(QScreen *screen);

	QPixmap makeScreenshot();
	QPixmap makeScreenshot( QScreen *screen );

private:
	Ui::dScreenSelectClass select_ui;

	QDialog *m_selectDialog = nullptr;

	QScreen *cursorScreen();
	QScreen *selectScreen();

	dDesktopManager();
};

#endif // DDESKTOPMANAGER_H
