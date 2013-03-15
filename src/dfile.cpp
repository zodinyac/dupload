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

#include "dfile.h"
#include "dsettings.h"

#include <QtGui/QImage>

dFile::dFile()
{
}

dFile::~dFile()
{
}

QString dFile::save( const QByteArray &arr, const QString &type )
{
	QString filePath;

	int saveType = dSettings::instance()->get( "s2fSaveType", 1 );
	if ( saveType == 1)
	{
		filePath = dSettings::instance()->get< QString >( "s2fDirectoryPath" );
	}
	else
	{
		filePath = QFileDialog::getExistingDirectory( 0, "Select directory where screenshot will be saved", QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

		if ( filePath.isNull() )
			return "E:IGNORE";
	}

	filePath += "/";
	filePath += QDateTime::currentDateTime().toString( "yyyy-MM-dd hh.mm.ss.zzz" );
	filePath += "." + type;

	QFile file( filePath );

	if ( !file.open( QIODevice::WriteOnly ) )
		return "E:0";

	file.write( arr );
	file.close();

	return filePath;
}
