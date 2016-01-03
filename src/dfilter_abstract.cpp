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

#include "dfilter_abstract.h"

dFilterAbstract::dFilterAbstract()
{
}

dFilterAbstract::~dFilterAbstract()
{
}

QString dFilterAbstract::name()
{
	return "Original";
}

QPixmap dFilterAbstract::applyFilter(const QPixmap &pixmap)
{
	return pixmap;
}