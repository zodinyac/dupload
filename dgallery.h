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

#ifndef DGALLERY_H
#define DGALLERY_H

#include <QDialog>

#include "dupload.h"
#include "ui_dgallery.h"

class dUpload;

class dGallery : public QDialog
{
	Q_OBJECT

public:
	dGallery( dUpload *d );
	~dGallery();

signals:
	void selected( const QString &id );

private slots:
	void on_createNew_clicked();
	void on_useLegacy_clicked();

	void on_createButton_clicked();
	void on_useButton_clicked();

	void finished( QNetworkReply *reply );

private:
	Ui::dGalleryClass ui;

	void setLayoutVisible( const QGridLayout *layout, bool visible = true );
	void setActiveLayout( const QGridLayout *layout );

	QGridLayout *activeLayout;

	dUpload *m_dupload;

	QNetworkAccessManager *m_netman;

};

#endif // DGALLERY_H