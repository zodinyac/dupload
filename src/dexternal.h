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

#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/QTimer>
#include "dupload.h"

class dUpload;

class dExternal : public QObject
{
	Q_OBJECT

public:
	dExternal( dUpload *d );
	~dExternal();

	static dExternal *instance( dUpload *d );

	void userRegister();
	void userAuth();

public slots:
	void finished( QNetworkReply *reply );
	void timerShot();

private:
	void get( const QString &w, const QString &p = "" );
	dUpload *m_dupload;

	QNetworkAccessManager *m_netman;

	QString m_passkey;
};

#endif // DEXTERNAL_H
