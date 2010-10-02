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

#include "dhighlighter.h"

dHighlighter::dHighlighter( dUpload *d ) : m_dupload( d )
{
	ui.setupUi( this );
	setAttribute( Qt::WA_DeleteOnClose );
	setAttribute( Qt::WA_QuitOnClose, false );

	m_pixmap = QPixmap::fromImage( QApplication::clipboard()->image() );
	if ( m_pixmap.isNull() )
		m_pixmap = QPixmap::grabWindow( QApplication::desktop()->winId() );

	ui.image->setPixmap( m_pixmap );

	m_painter.setRenderHint( QPainter::Antialiasing );
	m_painter.setPen( QPen( Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );
	m_painter.begin( &m_pixmap );

	showMaximized();

	#if defined( Q_WS_X11 )
		XClientMessageEvent xev;
		xev.type = ClientMessage;
		xev.window = winId();
		xev.message_type = XInternAtom( QX11Info::display(), "_NET_ACTIVE_WINDOW", False );
		xev.format = 32;
		xev.data.l[0] = 2;
		xev.data.l[1] = QX11Info::appUserTime();

		XSendEvent( QX11Info::display(), QX11Info::appRootWindow(), False, ( SubstructureNotifyMask | SubstructureRedirectMask ), ( XEvent * ) &xev );
	#else
		activateWindow();
		raise();
	#endif
}

dHighlighter::~dHighlighter()
{
}

void dHighlighter::keyPressEvent( QKeyEvent *event )
{
#if defined( Q_WS_WIN ) || defined( Q_WS_MAC )
	quint32 key = event->nativeVirtualKey();
#elif defined( Q_WS_X11 )
	quint32 key = event->nativeScanCode();
#endif

	if ( key == m_dupload->nativeKeycode( 'B' ) )
	{
		QApplication::clipboard()->setImage( m_pixmap.toImage() );
		m_dupload->sendFromClipboard();
		close();
	}
	else if ( key == m_dupload->nativeKeycode( 'N' ) )
	{
		QApplication::clipboard()->setImage( m_pixmap.toImage() );
		m_dupload->sendFromClipboard( 1 );
		close();
	}
	else if ( key == m_dupload->nativeKeycode( 'Z' ) )
	{
		if ( !m_states.isEmpty() )
		{
			m_pixmap = m_states.pop();
			ui.image->setPixmap( m_pixmap );
		}
	}
}

void dHighlighter::mousePressEvent( QMouseEvent *event )
{
	if ( m_states.size() >= 7 )
		m_states.remove( 0 );
	m_states.push( m_pixmap );

	m_lastPos = event->pos() + QPoint( 1, 0 );
	mouseMoveEvent( event );
}

void dHighlighter::mouseMoveEvent( QMouseEvent *event )
{
	if( !( event->buttons() & Qt::LeftButton ) || m_lastPos == QPoint( -1, -1 ) )
		return;

	QPoint scrollBarShift( ui.scrollArea->horizontalScrollBar()->value(), ui.scrollArea->verticalScrollBar()->value() );
	m_painter.drawLine( m_lastPos + scrollBarShift, event->pos() + scrollBarShift );
	m_lastPos = event->pos();

	ui.image->setPixmap( m_pixmap );
}

void dHighlighter::mouseReleaseEvent( QMouseEvent * /*event*/ )
{
	m_lastPos = QPoint( -1, -1 );
}
