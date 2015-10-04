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

#ifndef DIMAGEVIEW_H
#define DIMAGEVIEW_H

#include <QtWidgets/QLabel>
#include <QtNetwork/QtNetwork>

class dImageView : public QLabel
{
	Q_OBJECT

public:
	dImageView( const QString &id, QWidget *parent = 0 );
	~dImageView();

public slots:
	void finished( QNetworkReply *reply );

signals:
	void clicked( const QString &url );

protected:
	void mousePressEvent( QMouseEvent * event );

private:
	QString m_image;

	QNetworkAccessManager m_netman;
};

#endif // DIMAGEVIEW_H
