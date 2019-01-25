/****************************************************************************
 *  dUpload
 *
 *  Copyright (c) 2012, 2015 by Belov Nikita <null@deltaz.org>
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

#ifndef DWEBCAM_H
#define DWEBCAM_H

#include <QtGlobal>
#include <QtGui/QClipboard>
#include <QtMultimedia/QtMultimedia>
#include <QtMultimediaWidgets/QtMultimediaWidgets>
#include <QtWidgets/QtWidgets>
#include "dupload.h"
#include "ui_dwebcam.h"
#include "ui_dwebcamselect.h"

class dWebCam : public QWidget
{
	Q_OBJECT

public:
	dWebCam( dUpload *d );
	~dWebCam();

public slots:
	void cameraError( QCamera::Error value );
	void cameraStateChanged( QCamera::State state );
	void capture( bool checked = false );

protected:
	bool event( QEvent *event );
	void mouseMoveEvent( QMouseEvent* event );
	void mousePressEvent( QMouseEvent* event );
	void paintEvent( QPaintEvent *event );
	void resizeEvent( QResizeEvent *event );

private:
	void aeroBackground();

	Ui::dWebCamClass ui;
	Ui::dWebCamSelectClass select_ui;
	dUpload *m_dupload;

	QPoint m_drag_pos;

	static QByteArray m_defaultDevice;
	QDialog *m_selectDialog;

	QPointer< QCamera > m_camera;
	QPointer< QCameraImageCapture > m_imageCapture;

	QPixmap m_pixmap;

	QTimer *m_timer;

	int m_timerPaintState;
};

#endif // DWEBCAM_H
