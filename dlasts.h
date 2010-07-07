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

#ifndef DLASTS_H
#define DLASTS_H

#include <QClipboard>
#include <QDialog>
#include "dupload.h"
#include "ui_dlasts.h"

class dLasts : public QDialog
{
	Q_OBJECT

public:
	dLasts( dUpload *d );
	~dLasts();

public slots:
	void copyLinkToClipboard( const QUrl &url );

protected:
	bool eventFilter( QObject *o, QEvent *e );

private:
	Ui::dLastsClass ui;

	dUpload *m_dupload;
};

#endif // DLASTS_H
