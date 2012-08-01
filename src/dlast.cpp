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

#include "dlast.h"

dLast::dLast( dUpload *d ) : m_dupload( d ), QDialog( d )
{
	ui.setupUi( this );
	setAttribute( Qt::WA_DeleteOnClose );
	setAttribute( Qt::WA_QuitOnClose, false );

	ui.webView->installEventFilter( this );
	ui.webView->page()->setLinkDelegationPolicy( QWebPage::DelegateAllLinks );
	ui.webView->setUrl( "http://i.deltaz.org/last/" + m_dupload->passkey() );

	connect( ui.webView->page(), SIGNAL( linkClicked( const QUrl & ) ), this, SLOT( copyLinkToClipboard( const QUrl & ) ) );

	show();
}

dLast::~dLast()
{
}

void dLast::copyLinkToClipboard( const QUrl &url )
{
	QApplication::clipboard()->setText( url.toString() );
	m_dupload->notify( "Link was successfully copied to clipboard" );
}

bool dLast::eventFilter( QObject *o, QEvent *e )
{
	if ( e->type() == QEvent::ContextMenu )
		return true;
	return QObject::eventFilter( o, e );
}
