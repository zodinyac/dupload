/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2010, 2012, 2015 by Belov Nikita <null@deltaz.org>
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

#include <QJsonDocument>

#include "dlast.h"
#include "dimageview.h"

dLast::dLast( dUpload *d ) : m_dupload( d ), QDialog( d )
{
	ui.setupUi( this );
	setAttribute( Qt::WA_DeleteOnClose );
	setAttribute( Qt::WA_QuitOnClose, false );

	QPalette pal = palette();
	pal.setColor( QPalette::Background, Qt::white );
	setAutoFillBackground( true );
	setPalette( pal );

	ui.verticalLayout_2->setAlignment( Qt::AlignCenter );

	connect( &m_netman, &QNetworkAccessManager::finished, [=]( QNetworkReply *reply )
		{
			QUrl redirectUrl = reply->attribute( QNetworkRequest::RedirectionTargetAttribute ).toUrl();
			if ( !redirectUrl.isEmpty() )
			{
				m_netman.get( QNetworkRequest( redirectUrl ));
			}
			else
			{
				QJsonDocument json_doc = QJsonDocument::fromJson( reply->readAll() );
				if ( !json_doc.isArray() )
				{
					ui.mainLabel->setText( "Error while loading last images." );
				}
				else
				{
					ui.mainLabel->setAlignment( Qt::AlignTop );
					ui.mainLabel->setText( "<p align=\"center\"><span style=\"font-size: 0.8em; font-family:Lucida,sans-serif; font-weight:800;\">Click on image for copy link to clipboard</span></p>" );

					QJsonArray images = json_doc.array();
					for ( auto &image : images )
					{
						QJsonObject object = image.toObject();

						QString id = object.value( "id" ).toString();
						dImageView *image_view = new dImageView( id, this );
						ui.verticalLayout_2->addWidget( image_view );
						connect( image_view, SIGNAL( clicked( const QString & ) ), this, SLOT( copyLinkToClipboard( const QString & ) ) );

						QString time = QString( "<p align=\"center\"><span style=\"font-size: 0.7em; font-family:Lucida,sans-serif; font-weight:800; margin-bottom:10px; margin-top:-5px;\">Published at %1</span></p>" ).arg( object.value( "time" ).toString() );
						QLabel *time_label = new QLabel( time, this );
						ui.mainLabel->setAlignment( Qt::AlignHCenter );
						time_label->setTextInteractionFlags( Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse );
						ui.verticalLayout_2->addWidget( time_label );
					}
				}
			}
			reply->deleteLater();
		}
	);

	m_netman.get( QNetworkRequest( "http://vfc.cc/last/" + m_dupload->passkey() + "&json" ) );

	show();
}

dLast::~dLast()
{
}

void dLast::copyLinkToClipboard( const QString &url )
{
	QApplication::clipboard()->setText( url );
	m_dupload->notify( "Link was successfully copied to clipboard" );
}
