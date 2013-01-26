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

#include "dpainter.h"

dPainter::dPainter( QWidget * /*parent*/ )
{
	m_currentAction.type = ACTION_NONE;
	m_opacity = 1.0;
}

dPainter::~dPainter()
{
	while ( m_actions.size() )
		delete m_actions.pop().data;

	if ( m_currentAction.type != ACTION_NONE )
		delete m_currentAction.data;
}

void dPainter::drawPoint( const QPoint &point )
{
	m_currentAction.type = ACTION_POINT;
	m_currentAction.data = new QPoint( point );
	m_currentAction.opacity = m_opacity;
	m_currentAction.pen = m_pen;

	m_actions.push( m_currentAction );

	draw( &m_pixmap );
	QLabel::setPixmap( m_pixmap );

	m_currentAction.type = ACTION_NONE;
}

void dPainter::drawPath( const QPainterPath &path, bool save )
{
	m_currentAction.type = ACTION_PATH;
	m_currentAction.data = new QPainterPath( path );
	m_currentAction.opacity = m_opacity;
	m_currentAction.pen = m_pen;

	if ( save )
	{
		m_actions.push( m_currentAction );

		draw( &m_pixmap );
		QLabel::setPixmap( m_pixmap );

		m_currentAction.type = ACTION_NONE;
	}
	else
	{
		update();
	}
}

double dPainter::opacity()
{
	return m_opacity;
}

void dPainter::setOpacity( double opacity )
{
	m_opacity = opacity;
}

const QPen &dPainter::pen()
{
	return m_pen;
}

void dPainter::setPen( const QPen &pen )
{
	m_pen = pen;
}

const QPixmap &dPainter::pixmap()
{
	return m_pixmap;
}

void dPainter::setPixmap( const QPixmap &pixmap )
{
	m_pixmap = m_pixmap_orig = pixmap;
	QLabel::setPixmap( m_pixmap );
}

void dPainter::undo()
{
	if ( !m_actions.size() )
		return;

	delete m_actions.pop().data;
	m_pixmap = m_pixmap_orig;

	foreach ( m_currentAction, m_actions )
		draw( &m_pixmap );

	QLabel::setPixmap( m_pixmap );
	m_currentAction.type = ACTION_NONE;
}

void dPainter::draw( QPaintDevice *device )
{
	QPainter painter( device );

	painter.setOpacity( m_currentAction.opacity );
	painter.setPen( m_currentAction.pen );
	painter.setRenderHint( QPainter::Antialiasing );

	if ( m_currentAction.type == ACTION_POINT )
	{
		painter.drawPoint( *( QPoint * )m_currentAction.data );
	}
	else if ( m_currentAction.type == ACTION_PATH )
	{
		painter.drawPath( *( QPainterPath * )m_currentAction.data );
	}
}

void dPainter::paintEvent( QPaintEvent *event )
{
	QLabel::paintEvent( event );

	if ( m_currentAction.type == ACTION_NONE )
		return;

	draw( this );
}
