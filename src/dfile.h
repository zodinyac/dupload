/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2013 by Belov Nikita <null@deltaz.org>
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

#ifndef DFILE_H
#define DFILE_H

#include <QtCore/QtCore>

class dFile : public QObject
{
	Q_OBJECT

public:
	dFile();
	~dFile();

	QString save( const QByteArray &arr, const QString &type );

private:

};

#endif // DFILE_H
