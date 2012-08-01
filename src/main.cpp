/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2009-2010, 2012 by Belov Nikita <null@deltaz.org>
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

#include "dupload.h"
#include <QtWidgets/QApplication>

int main( int argc, char *argv[] )
{
	QTextCodec *codec = QTextCodec::codecForName( "UTF-8" );
	QTextCodec::setCodecForLocale( codec );

	QString file;
	if ( argc >= 2 )
		file = argv[1];

	QApplication a( argc, argv );

	dUpload w( file );
	w.show( Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint );

	return a.exec();
}
