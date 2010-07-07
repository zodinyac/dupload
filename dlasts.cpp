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

#include "dlasts.h"

dLasts::dLasts( dUpload *d ) : m_dupload( d ), QDialog( d )
{
	ui.setupUi( this );
	setAttribute( Qt::WA_DeleteOnClose );

	ui.webView->installEventFilter( this );
	ui.webView->page()->setLinkDelegationPolicy( QWebPage::DelegateAllLinks );
	ui.webView->setUrl( "http://i.deltaz.org/lasts/" + m_dupload->passkey() );

	connect( ui.webView->page(), SIGNAL( linkClicked( const QUrl & ) ), this, SLOT( copyLinkToClipboard( const QUrl & ) ) );

	show();
}

dLasts::~dLasts()
{
}

void dLasts::copyLinkToClipboard( const QUrl &url )
{
	QApplication::clipboard()->setText( url.toString() );
	m_dupload->notify( "Link was successfully copied to clipboard" );
}

bool dLasts::eventFilter( QObject *o, QEvent *e )
{
	if ( e->type() == QEvent::ContextMenu )
		return true;
	return QObject::eventFilter( o, e );
}
