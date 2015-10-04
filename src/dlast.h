/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2010 by Belov Nikita <null@deltaz.org>
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

#ifndef DLAST_H
#define DLAST_H

#include <QtGui/QClipboard>
#include <QtWidgets/QDialog>
#include "dupload.h"
#include "ui_dlast.h"

class dLast : public QDialog
{
	Q_OBJECT

public:
	dLast( dUpload *d );
	~dLast();

public slots:
	void copyLinkToClipboard( const QString &url );

private:
	Ui::dLastClass ui;

	QNetworkAccessManager m_netman;

	dUpload *m_dupload;
};

#endif // DLAST_H
