//	Copyright (c) 2013, Michal Ulianko
//	All rights reserved.
//
//	Redistribution and use in source and binary forms, with or without
//	modification, are permitted provided that the following conditions are met:
//
//	1. Redistributions of source code must retain the above copyright notice, this
//	   list of conditions and the following disclaimer.
//	2. Redistributions in binary form must reproduce the above copyright notice,
//	   this list of conditions and the following disclaimer in the documentation
//	   and/or other materials provided with the distribution.
//
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
//	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef FPV_H_
#define FPV_H_

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <QResizeEvent>
#include <QtNetwork>

#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/Init>
#include <QGst/Pipeline>
#include <QGst/ElementFactory>
#include <QGst/Pad>
#include <QGst/Structure>
#include <QGst/Bus>
#include <QGst/Message>
#include <QGst/Ui/VideoWidget>

#include "hud.h"

class Fpv : public QWidget
{
	Q_OBJECT

public:
	Fpv(QWidget *parent = 0);
	virtual ~Fpv();

public slots:
	void startFpv();
	void stopFpv();

protected slots:
	void readDatagrams();

protected:
	virtual void resizeEvent(QResizeEvent *event);
	QUdpSocket *socket;
	QGst::PipelinePtr pipeline;
	QGst::Ui::VideoWidget *videoWidget;
	QGst::ElementPtr output;
	void onRtpBinPadAdded(const QGst::PadPtr & pad);
	void onBusErrorMessage(const QGst::MessagePtr & msg);
	Hud *hud;
	int retryCount;
	bool retryEnable;
	QTimer *retryTimer;

private:
	Q_DISABLE_COPY(Fpv);
};

#endif /* FPV_H_ */
