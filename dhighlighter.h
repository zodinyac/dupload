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

#include <QClipboard>
#include <QScrollBar>
#include <QWidget>
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

	QImage m_image;
	QPoint m_lastPos;
};

#endif // DHIGHLIGHTER_H
