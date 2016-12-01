/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2012-2013, 2015 by Belov Nikita <null@deltaz.org>
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

	void show( int index = 0 );

	template < class T >
	inline T get( const QString &key, const T &default_value = T() )
	{
		return m_settings.value( key, QVariant::fromValue( default_value ) ).template value< T >();
	}

	template < class T >
	void set( const QString &key, const T &value );

	int remove( const QString &key );

signals:
	void settingsChanged();

private:
	Ui::dSettingsClass m_settingsUi;
	QPointer< QDialog > m_settingsDialog;

	dSettings();

	void s2fSetEnabled( bool enabled = true );

	void highlighterSettingsLoad();
	void highlighterSettingsColor( bool checked = false );
	void highlighterSettingsWidth( double value );

	void screenSettingsLoad();
	void screenSettingsRadio( bool checked = false );

	void serverSettingsLoad();

	QHash< QString, QVariant > m_settings;
};

#endif // DSETTINGS_H
