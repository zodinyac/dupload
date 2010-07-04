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

#include "droparea.h"

dropArea::dropArea( QWidget *parent ) : QLabel( parent )
{
    setFrameStyle( QFrame::Sunken | QFrame::StyledPanel );
    setAlignment( Qt::AlignCenter );
    setAcceptDrops( true );

	locked = false;

	settext( "drop\nhere" );
}

void dropArea::lock( bool l )
{
	locked = l;
	if ( !l )
		settext( "drop\nhere" );
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
			settext( QString::number( QFileInfo( event->mimeData()->urls().at(0).toLocalFile() ).size() ) );
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
	emit changed( event->mimeData()->urls().at(0).toLocalFile() );
	event->acceptProposedAction();
}
