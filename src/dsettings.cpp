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

#include "dsettings.h"

dSettings::dSettings()
{
	m_shown = false;
}

dSettings::~dSettings()
{
}

dSettings *dSettings::instance()
{
	static dSettings *me = new dSettings();

	return me;
}

void dSettings::show()
{
	if ( m_shown )
		return;

	m_shown = true;

	QDialog settingsDialog;
	Ui::dSettingsClass settingsUi;

	settingsUi.setupUi( &settingsDialog );

	// dialog
	settingsDialog.setAttribute( Qt::WA_QuitOnClose, false );
	settingsDialog.setWindowFlags( settingsDialog.windowFlags() ^ Qt::WindowContextHelpButtonHint );

	// mpc screens path
	settingsUi.pathMpcEdit->setText( get< QString >( "mpcScreensPath" ) );

	// enable mpc checkbox
	connect( settingsUi.enableMpcCheckBox, &QCheckBox::toggled, [ this, &settingsUi ]( bool checked )
		{
			set( "enableMpc", checked );

			settingsUi.folderMpcLabel->setEnabled( checked );
			settingsUi.browseMpcButton->setEnabled( checked );
			settingsUi.pathMpcEdit->setEnabled( checked );

			// set path to snapshotpath from registry (or home) if it doesn't exist
			if ( settingsUi.pathMpcEdit->text().isEmpty() || !QDir( settingsUi.pathMpcEdit->text() ).exists() )
				settingsUi.pathMpcEdit->setText( QSettings( "HKEY_CURRENT_USER\\Software\\Gabest\\Media Player Classic\\Settings", QSettings::NativeFormat ).value( "SnapShotPath", QDir::homePath() ).toString() );

			set( "mpcScreensPath", settingsUi.pathMpcEdit->text() );
		}
	);

	settingsUi.enableMpcCheckBox->setChecked( get( "enableMpc", false ) );
	settingsUi.enableMpcCheckBox->toggled( settingsUi.enableMpcCheckBox->isChecked() );

	// browse mpc button
	connect( settingsUi.browseMpcButton, &QPushButton::clicked, [ this, &settingsDialog, &settingsUi ]( bool )
		{
			QString dir = QFileDialog::getExistingDirectory( &settingsDialog, "Select the mpc screenshots directory", settingsUi.pathMpcEdit->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

			settingsUi.pathMpcEdit->setText( dir );
			set( "mpcScreensPath", dir );
		}
	);

	// close button
	connect( settingsUi.closeButton, &QPushButton::clicked, [ &settingsDialog ]( bool )
		{
			settingsDialog.accept();
		}
	);

	settingsDialog.exec();

	m_shown = false;
}

template < class T >
T dSettings::get( const QString &key, const T &default )
{
	return m_settings.value( key, QVariant::fromValue( default ) ).value< T >();
}

template < class T >
void dSettings::set( const QString &key, const T &value )
{
	m_settings.insert( key, QVariant::fromValue( value ) );

	emit settingsChanged();
}

int dSettings::remove( const QString &key )
{
	return m_settings.remove( key );
}
