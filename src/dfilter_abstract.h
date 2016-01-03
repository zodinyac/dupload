/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2015 by Belov Nikita <null@deltaz.org>
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

#ifndef DFILTERABSTACT_H
#define DFILTERABSTACT_H

#include <QtCore/QObject>
#include <QtGui/QPixmap>

class dFilterAbstract : public QObject
{
	Q_OBJECT

public:
	dFilterAbstract();
	~dFilterAbstract();

	virtual QString name();
	virtual QPixmap applyFilter(const QPixmap &pixmap);
};

#endif // DFILTERABSTACT_H
