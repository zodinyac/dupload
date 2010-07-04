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

#ifndef DROPAREA_H
#define DROPAREA_H

#include <QLabel>
#include <QUrl>
#include <QFileInfo>
#include <QDropEvent>

class dropArea : public QLabel
{
	Q_OBJECT

public:
	dropArea( QWidget *parent=0 );
	void lock( bool l = true );
	void settext( QString text );

signals:
	void changed( const QString &fileName );
	void clicked();

protected:
	void dragEnterEvent( QDragEnterEvent *event );
	void dragLeaveEvent( QDragLeaveEvent *event );
	void dragMoveEvent( QDragMoveEvent *event );
	void dropEvent( QDropEvent *event );
	void mousePressEvent( QMouseEvent *event );

private:
	QLabel *label;
	bool locked;
};

#endif // DROPAREA_H
