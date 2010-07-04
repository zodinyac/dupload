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
#include <QDesktopWidget>
#include <QPixmap>
#include <QFile>
#include <QClipboard>
#include <QtNetwork>
#include "qtwin.h"
#include "ui_dupload.h"
#include "droparea.h"
#include "dpreview.h"

#if defined( Q_OS_WIN )
	#include <lmcons.h>
	#include <windows.h>
#elif defined( Q_OS_MAC ) || defined( Q_OS_FREEBSD ) || defined( Q_OS_LINUX ) || defined( Q_OS_UNIX )
	#include <pwd.h>
	#include <unistd.h>
#endif

class dUpload : public QWidget
{
	Q_OBJECT

public:
	dUpload( const QString &file, QWidget *parent = 0 );
	~dUpload();

public slots:
	void progress( qint64 received, qint64 total );
	void finished( QNetworkReply *reply );
	void changed( const QString &file );
	void clicked();

protected:
	void keyPressEvent( QKeyEvent *event );
	void mouseMoveEvent( QMouseEvent* event );
	void mousePressEvent( QMouseEvent* event );
	
private:
	void load( const QByteArray &arr, const QString &type, const QString &filename );

	Ui::dUploadClass ui;

	QPoint m_drag_pos;

	dPreview *m_preview;

	dropArea *droparea;
	QNetworkAccessManager *m_netman;
	QString m_userlogin;
	QString m_link;
	QString m_filename;
};

#endif // DUPLOAD_H
