/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2010, 2012 by Belov Nikita <null@deltaz.org>
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

#include "dgallery.h"

dGallery::dGallery( dUpload *d ) : m_dupload( d ), QDialog( d )
{
	ui.setupUi( this );
	setAttribute( Qt::WA_DeleteOnClose );
	setAttribute( Qt::WA_QuitOnClose, false );

	activeLayout = 0;

	setLayoutVisible( ui.selectLayout, false );
	setLayoutVisible( ui.newLayout, false );
	setLayoutVisible( ui.useLayout, false );

	show();

	setActiveLayout( ui.selectLayout );

	m_netman = new QNetworkAccessManager();
	connect( m_netman, SIGNAL( finished( QNetworkReply * ) ), this, SLOT( finished( QNetworkReply * ) ) );
}

dGallery::~dGallery()
{
}

void dGallery::setLayoutVisible( const QGridLayout *layout, bool visible )
{
	if ( !layout )
		return;

	int rowCount = layout->rowCount();
	int columnCount = layout->columnCount();

	for ( int i = 0; i < rowCount; i++ )
		for ( int j = 0; j < columnCount; j++ )
		{
			QWidget *w = layout->itemAtPosition( i, j )->widget();
			if ( w )
				w->setVisible( visible );
		}

	adjustSize();
}

void dGallery::setActiveLayout( const QGridLayout *layout )
{
	if ( activeLayout )
		setLayoutVisible( activeLayout, false );

	activeLayout = ( QGridLayout * )layout;
	setLayoutVisible( activeLayout, true );
}

void dGallery::on_createNew_clicked()
{
	setActiveLayout( ui.newLayout );
}

void dGallery::on_useLegacy_clicked()
{
	setActiveLayout( ui.useLayout );
}

void dGallery::on_createButton_clicked()
{
	if ( ui.nameEdit->text().isEmpty() )
	{
		QMessageBox::warning( m_dupload, "", "Name can't be empty." );

		return;
	}
	if ( ui.descEdit->toPlainText().isEmpty() )
	{
		QMessageBox::warning( m_dupload, "", "Description can't be empty." );

		return;
	}

	ui.createButton->setDisabled( true );

	QByteArray data;
	data.append( "n=" + QUrl::toPercentEncoding( ui.nameEdit->text() ) + "&d=" + QUrl::toPercentEncoding( ui.descEdit->toPlainText() ) + "&p=" + m_dupload->passkey() );

	QNetworkRequest request( QUrl( QString( "http://%1/gallery.php" ).arg( dSettings::instance()->get< QString >( "serverAddress" ) ) ) );
	request.setRawHeader( "Content-Type", QString( "application/x-www-form-urlencoded; charset=utf-8" ).toUtf8() );
	m_netman->post( request, data );
}

void dGallery::on_useButton_clicked()
{
	if ( ui.idEdit->text().isEmpty() )
	{
		QMessageBox::warning( m_dupload, "", "ID can't be empty." );

		return;
	}

	ui.useButton->setDisabled( true );

	m_netman->get( QNetworkRequest ( QUrl( "http://" + dSettings::instance()->get< QString >( "serverAddress" ) + "/gallery.php?i=" + ui.idEdit->text().right( 32 ) + "&d=1" ) ) );
}

void dGallery::finished( QNetworkReply *reply )
{
	QString r = reply->readAll();

	if ( !ui.nameEdit->text().isEmpty() )
	{
		if ( r.length() == 32 )
		{
			emit selected( r );

			reject();
		}
		else
		{
			ui.createButton->setDisabled( false );

			QMessageBox::critical( m_dupload, "", "Unknown error." );
		}
	}
	else if ( !ui.idEdit->text().isEmpty() )
	{
		if ( r.length() == 3 )
		{
			ui.useButton->setDisabled( false );

			QMessageBox::critical( m_dupload, "", "Gallery's id isn't correct." );
		}
		else
		{
			emit selected( ui.idEdit->text().right( 32 ) );

			reject();
		}
	}
}
