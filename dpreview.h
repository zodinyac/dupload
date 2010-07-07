/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2009 by Belov Nikita <null@deltaz.org>
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

#ifndef DPREVIEW_H
#define DPREVIEW_H

#include <QWidget>
#include <QDialog>
#include <QtNetwork>
#include "ui_dpreview.h"

class dPreview : public QDialog
{
	Q_OBJECT

public:
	dPreview( const QString &link, QWidget *parent = 0 );
	~dPreview();

public slots:
	void progress( qint64 received, qint64 total );
	void finished( QNetworkReply *reply );

private:
	Ui::dPreviewClass ui;

	QNetworkAccessManager *m_netman;
};

#endif // DPREVIEW_H
