/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2013 by Belov Nikita <null@deltaz.org>
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

#ifndef DPAINTER_H
#define DPAINTER_H

#include <QtCore/QStack>
#include <QtGui/QPainter>
#include <QtWidgets/QLabel>

class dPainter : public QLabel
{
	Q_OBJECT

public:
	dPainter( QWidget *parent = 0 );
	~dPainter();

	void drawPoint( const QPoint &point );
	void drawPath( const QPainterPath &path, bool save = false );

	double opacity();
	void setOpacity( double opacity );

	const QPen &pen();
	void setPen( const QPen &pen );

	const QPixmap &pixmap();
	void setPixmap( const QPixmap &pixmap );

	void undo();

protected:
	void paintEvent( QPaintEvent *event );

private:
	enum actionType
	{
		ACTION_NONE,
		ACTION_POINT,
		ACTION_PATH
	};

	struct action_t
	{
		actionType type;
		void *data;

		double opacity;
		QPen pen;
	};

	void draw( QPaintDevice *device );

	QPixmap m_pixmap;
	QPixmap m_pixmap_orig;

	double m_opacity;
	QPen m_pen;

	action_t m_currentAction;
	QStack< action_t > m_actions;
};

#endif // DPAINTER_H
