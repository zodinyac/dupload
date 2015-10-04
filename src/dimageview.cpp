/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2015 by Belov Nikita <zodiac.nv@gmail.com>
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

#include <QtGui/QMouseEvent>

#include "dimageview.h"

dImageView::dImageView( const QString &id, QWidget *parent ) : QLabel( parent )
{
	m_image = "http://vfc.cc/" + id;

	connect( &m_netman, SIGNAL( finished( QNetworkReply * ) ), this, SLOT( finished( QNetworkReply * ) ) );
	m_netman.get( QNetworkRequest( QUrl( "http://vfc.cc/t_" + id ) ) );

	setAlignment( Qt::AlignHCenter );
	setCursor( Qt::PointingHandCursor );
	setText( "Loading image... " );
}

dImageView::~dImageView()
{
}

void dImageView::finished( QNetworkReply *reply )
{
	QUrl redirectUrl = reply->attribute( QNetworkRequest::RedirectionTargetAttribute ).toUrl();
	if ( !redirectUrl.isEmpty() )
	{
		m_netman.get( QNetworkRequest( redirectUrl ) );
	}
	else
	{
		QPixmap img;
		img.loadFromData( reply->readAll() );

		setPixmap( img );
		setFixedSize( img.size() );

		reply->deleteLater();
	}
}

void dImageView::mousePressEvent( QMouseEvent *event )
{
	if ( event->button() == Qt::LeftButton )
	{
		emit clicked( m_image );
	}
}
