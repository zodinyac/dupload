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

#ifndef DPLAYERMPC_H
#define DPLAYERMPC_H

#include <QtCore/QtCore>

#include "dupload.h"

class dUpload;

class dPlayerMpc : public QObject
{
	Q_OBJECT

public:
	dPlayerMpc( dUpload *d );
	~dPlayerMpc();

private:
	void update();
	void directoryChanged( const QString &dir );

	dUpload *m_dupload;

	QFileSystemWatcher *m_watcher;

	bool m_enabled;

	QString m_dir;
	QStringList m_files;
};

#endif // DPLAYERMPC_H
