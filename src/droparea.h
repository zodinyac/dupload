/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2009, 2012 by Belov Nikita <null@deltaz.org>
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

#ifndef DROPAREA_H
#define DROPAREA_H

#include "dgallery.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtCore/QUrl>
#include <QtCore/QFileInfo>
#include <QtGui/QDropEvent>

class dUpload;
class dGallery;

class dropArea : public QLabel
{
	Q_OBJECT

public:
	dropArea( dUpload *d );
	void lock( bool l = true );
	void settext( QString text );
	bool isLocked();

signals:
	void changed( const QString &fileName, const QString &gid );
	void clicked();

private slots:
	void gallerySelected( const QString &id );
	void galleryClosed();
	void uploadFinished();

protected:
	void dragEnterEvent( QDragEnterEvent *event );
	void dragLeaveEvent( QDragLeaveEvent *event );
	void dragMoveEvent( QDragMoveEvent *event );
	void dropEvent( QDropEvent *event );
	void mousePressEvent( QMouseEvent *event );

private:
	QList< QUrl > m_urls;

	QLabel *label;
	bool locked;

	dGallery *m_gallery;
	dUpload *m_dupload;

	QString m_gid;

	int m_q;
};

#endif // DROPAREA_H
