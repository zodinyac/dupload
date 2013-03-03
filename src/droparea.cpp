/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2009, 2012-2013 by Belov Nikita <null@deltaz.org>
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

#include "droparea.h"

dropArea::dropArea( dUpload *d ) : m_dupload( d ), QLabel( d )
{
    setFrameStyle( QFrame::Sunken | QFrame::StyledPanel );
    setAlignment( Qt::AlignCenter );
    setAcceptDrops( true );

	auto effect = new QGraphicsDropShadowEffect();

	effect->setBlurRadius( 15 );
	effect->setColor( QColor( "white" ) );
	effect->setOffset( 0 );
	setGraphicsEffect( effect );

	locked = false;

	settext( "drop\nhere" );

	connect( m_dupload, SIGNAL( finished() ), this, SLOT( uploadFinished() ) );
}

void dropArea::lock( bool l )
{
	locked = l;
	if ( !l )
		settext( "drop\nhere" );
}

bool dropArea::isLocked()
{
	return locked;
}

void dropArea::settext( QString text )
{
	QString tpl = "<p align=\"center\"><span style=\"font-size:20pt; font-weight:600;\">%1</span></p>";
	text = text.replace( "\n", "<br/>" );
	setText( tpl.arg( text ) );
}

void dropArea::dragEnterEvent( QDragEnterEvent *event )
{
	if ( locked )
		return;

	if ( !event->mimeData()->hasUrls() )
		return;
	else
	{
		if ( !QFileInfo( event->mimeData()->urls().at(0).toLocalFile() ).isFile() )
			return;
		else
		{
			int c = 0;

			foreach( QUrl url, event->mimeData()->urls() )
				c += QFileInfo( url.toLocalFile() ).size();

			settext( QString::number( c ) );
		}
	}
	event->acceptProposedAction();
}

void dropArea::dragLeaveEvent( QDragLeaveEvent *event )
{
	settext( "drop\nhere" );
	event->accept();
}

void dropArea::dragMoveEvent( QDragMoveEvent *event )
{
	event->acceptProposedAction();
}

void dropArea::dropEvent( QDropEvent *event )
{
	settext( "..." );

	m_urls.clear();
	m_q = 0;
	
	if ( event->mimeData()->urls().size() > 1 && m_dupload->authorized() )
	{
		m_urls = event->mimeData()->urls();
		qSort( m_urls.begin(), m_urls.end(), []( const QUrl &url1, const QUrl &url2 )
				{
					return QFileInfo( url1.toLocalFile() ).lastModified() < QFileInfo( url2.toLocalFile() ).lastModified();
				}
			);

		lock();

		m_gallery = new dGallery( m_dupload );
		connect( m_gallery, SIGNAL( selected( const QString & ) ), this, SLOT( gallerySelected( const QString & ) ) );
		connect( m_gallery, SIGNAL( rejected() ), this, SLOT( galleryClosed() ) );
	}
	else
		emit changed( event->mimeData()->urls().at(0).toLocalFile(), "" );
	event->acceptProposedAction();
}

void dropArea::mousePressEvent( QMouseEvent * /*event*/ )
{
	emit clicked();
}

void dropArea::gallerySelected( const QString &id )
{
	m_gid = id;

	emit changed( m_urls.at( 0 ).toLocalFile(), m_gid );
}

void dropArea::galleryClosed()
{
	lock( false );
}

void dropArea::uploadFinished()
{
	m_q++;

	if ( m_q < m_urls.size() && m_urls.count() )
	{
		emit changed( m_urls.at( m_q ).toLocalFile(), m_gid );
	}
	else if ( m_q == m_urls.size() )
	{
		QString link = "http://i.deltaz.org/g" + m_gid;

		QApplication::clipboard()->setText( link );
		settext( "OK" );
		setToolTip( "Click here for copy link to clipboard\n" + link );
		m_dupload->notify( "Click here for copy link to clipboard\n" + link );
		m_dupload->setLink( link );
	}
}


