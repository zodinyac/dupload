/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2012 by Belov Nikita <null@deltaz.org>
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

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

#include "ui_dsettings.h"

#ifndef DSETTINGS_H
#define DSETTINGS_H

class dSettings : public QObject
{
	Q_OBJECT

public:
	~dSettings();

	static dSettings *instance();

	void show();

	template < class T >
	T get( const QString &key, const T &default = T() );

	template < class T >
	void set( const QString &key, const T &value );

	int remove( const QString &key );

signals:
	void settingsChanged();

private:
	dSettings();

	QHash< QString, QVariant > m_settings;

	bool m_shown;
};

#endif // DSETTINGS_H
