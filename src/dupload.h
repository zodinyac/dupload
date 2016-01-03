/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2009-2010, 2012-2013, 2015 by Belov Nikita <null@deltaz.org>
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

#include <QtWidgets/QWidget>
#include <QtWidgets/QDesktopWidget>
#include <QtGui/QPixmap>
#include <QtCore/QFile>
#include <QtGui/QClipboard>
#include <QtNetwork/QtNetwork>
#include "ui_dupload.h"
#include "droparea.h"
#include "dpreview.h"
#include "dtrayicon.h"
#include "dtaskbar.h"
#include "dexternal.h"
#include "dglobalhotkey.h"
#include "dlast.h"
#include "dhighlighter.h"
#include "dwebcam.h"
#include "dsettings.h"
#include "dplayermpc.h"
#include "dareaselector.h"
#include "ddll.h"
#include "dfile.h"
#include "dfilter.h"

#if defined( Q_OS_WIN )
	#include <lmcons.h>
	#include <windows.h>
#elif defined( Q_OS_MAC ) || defined( Q_OS_FREEBSD ) || defined( Q_OS_LINUX ) || defined( Q_OS_UNIX )
	#include <pwd.h>
	#include <unistd.h>
#endif

class dTrayIcon;
class dHighlighter;
class dropArea;
class dWebCam;
class dAreaSelector;
class dFilter;

class dUpload : public QWidget, public QAbstractNativeEventFilter
{
	Q_OBJECT

public:
	dUpload( const QString &file, QWidget *parent = 0 );
	~dUpload();

	void show();
	void show( Qt::WindowFlags flags );

	void sendFromClipboard( int type = 0, const QString &gallery = QString() );
	const QString &getUserLogin() { return m_userlogin; }

	bool authorized();

	void notify( const QString &m );
	void showLast();

	const QString &userlogin();
	void setUserlogin( const QString &userlogin = QString() );

	const QString &passkey();
	void setPasskey( const QString &passkey = QString() );

	void setLink( const QString &link = QString() );

	quint32 nativeKeycode( QChar key );

	bool nativeEventFilter( const QByteArray &eventType, void *event, long *result );

signals:
	void finished();

public slots:
	void progress( qint64 received, qint64 total );
	void finished( QNetworkReply *reply );
	void changed( const QString &file, const QString &gallery = QString() );
	void clicked();
	void hotKeyPressed( quint32 k );

protected:
	void closeEvent( QCloseEvent *event );
	void keyPressEvent( QKeyEvent *event );
	void mouseMoveEvent( QMouseEvent* event );
	void mousePressEvent( QMouseEvent *event );
	void paintEvent( QPaintEvent *event );
	bool event( QEvent *event );
	
private:
	void aeroBackground();
	void load( const QByteArray &arr, const QString &type, const QString &filename, const QString &gallery = QString(), bool autoConvert = false );

	Ui::dUploadClass ui;

	QPoint m_drag_pos;

	dTrayIcon *m_trayicon;

	dDll *m_dll;
	dFile *m_file;

	QIcon m_icon;

	dropArea *droparea;
	QNetworkAccessManager *m_netman;
	QString m_userlogin;
	QString m_passkey;
	QString m_link;
	QString m_filename;

	bool m_logged;

	QPointer< dWebCam > m_dwebcam;
	bool m_webcam_creating;

	QPointer< dAreaSelector > m_dareaselector;
};

#endif // DUPLOAD_H
