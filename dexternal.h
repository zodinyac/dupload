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

#ifndef DEXTERNAL_H
#define DEXTERNAL_H

#include <QInputDialog>
#include <QMessageBox>
#include "dupload.h"

class dUpload;

class dExternal : public QObject
{
	Q_OBJECT

public:
	dExternal( dUpload *d );
	~dExternal();

	static dExternal *instance( dUpload *d );

public slots:
	void finished( QNetworkReply *reply );

private:
	void get( const QString &w, const QString &p = "" );
	dUpload *m_dupload;

	QNetworkAccessManager *m_netman;
};

#endif // DEXTERNAL_H
