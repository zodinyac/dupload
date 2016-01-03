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

#ifndef DFILTERMONOCHROME_H
#define DFILTERMONOCHROME_H

#include "dfilter_abstract.h"

class dFilterMonochrome : public dFilterAbstract
{
	Q_OBJECT

public:
	dFilterMonochrome();
	~dFilterMonochrome();

	QString name();
	QPixmap applyFilter(const QPixmap &pixmap);

private:

};

#endif // DFILTERMONOCHROME_H
