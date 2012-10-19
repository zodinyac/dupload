/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2012 by Belov Nikita <null@deltaz.org>
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

#ifndef DAREASELECTOR_H
#define DAREASELECTOR_H

#include <QtGui/QClipboard>
#include <QtGui/QPainter>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>
#include "dupload.h"

class dAreaSelector : public QWidget
{
	Q_OBJECT

public:
	dAreaSelector( dUpload *d );
	~dAreaSelector();

protected:
	void keyPressEvent( QKeyEvent *event );
	void mousePressEvent( QMouseEvent *event );
	void mouseMoveEvent( QMouseEvent *event );
	void mouseReleaseEvent( QMouseEvent *event );
	void paintEvent( QPaintEvent *event );

private:
	void drawSelection( QPainter &painter );
	dUpload *m_dupload;

	QPixmap m_backgroundPixmap;
	QPixmap m_pixmap;

	QPoint m_startPos;
	QPoint m_endPos;

	QRect m_selection;

	bool m_processSelection;
};

#endif // DAREASELECTOR_H
