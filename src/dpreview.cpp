/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2009, 2012 by Belov Nikita <null@deltaz.org>
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

#include "dpreview.h"
#include <QtWidgets/QMessageBox>

dPreview::dPreview( const QString &link, QWidget *parent ) : QDialog( parent )
{
	ui.setupUi( this );
	ui.label->setVisible( false );
	setAttribute( Qt::WA_DeleteOnClose );

	m_netman = new QNetworkAccessManager();
	connect( m_netman, SIGNAL( finished( QNetworkReply * ) ), this, SLOT( finished( QNetworkReply * ) ) );

	QNetworkReply* netr = m_netman->get( QNetworkRequest( QUrl( "http://vfc.cc/t_" + link ) ) );
	connect( netr, SIGNAL( downloadProgress( qint64, qint64 ) ), this, SLOT( progress( qint64, qint64 ) ) );

	show();
}

dPreview::~dPreview()
{
}


void dPreview::progress( qint64 received, qint64 total )
{
	ui.progress->setMaximum( total );
	ui.progress->setValue( received );
}

void dPreview::finished( QNetworkReply *reply )
{
	QUrl redirectUrl = reply->attribute( QNetworkRequest::RedirectionTargetAttribute ).toUrl();
	if ( !redirectUrl.isEmpty() )
	{
		m_netman->get( QNetworkRequest( redirectUrl ) );
	}
	else
	{
		QPixmap img;
		img.loadFromData( reply->readAll() );

		ui.progress->setVisible( false );
		ui.label->setVisible( true );
		ui.label->setPixmap( img );
	}

	reply->deleteLater();
}
