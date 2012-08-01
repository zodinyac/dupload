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

#ifndef DHIGHLIGHTER_H
#define DHIGHLIGHTER_H

#include <QtGui/QClipboard>
#include <QtGui/QPainter>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>
#include "dupload.h"
#include "ui_dhighlighter.h"

class dHighlighter : public QWidget
{
	Q_OBJECT

public:
	dHighlighter( dUpload *d );
	~dHighlighter();

protected:
	void keyPressEvent( QKeyEvent *event );
	void mousePressEvent( QMouseEvent *event );
	void mouseMoveEvent( QMouseEvent *event );
	void mouseReleaseEvent( QMouseEvent *event );

private:
	Ui::dHighlighterClass ui;
	dUpload *m_dupload;

	QPixmap m_pixmap;
	QPainter m_painter;
	QPoint m_lastPos;

	QStack< QPixmap > m_states;
};

#endif // DHIGHLIGHTER_H
