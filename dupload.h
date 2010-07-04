/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2009 by Belov Nikita <null@deltaz.ru>
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

#ifndef DUPLOAD_H
#define DUPLOAD_H

#include <QWidget>
#include <QPixmap>
#include <QFile>
#include <QClipboard>
#include <QtNetwork>
#include "ui_dupload.h"
#include "droparea.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <lmcons.h>
#endif

class dUpload : public QWidget
{
	Q_OBJECT

public:
	dUpload( QWidget *parent = 0 );
	~dUpload();

public slots:
	void progress( qint64 received, qint64 total );
	void finished( QNetworkReply *reply );
	void changed( const QString &file );

private:
	Ui::dUploadClass ui;

	dropArea *droparea;
	QNetworkAccessManager *m_netman;
	QString m_userlogin;
};

#endif // DUPLOAD_H
