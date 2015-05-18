#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <QResizeEvent>
#include <QtNetwork>

#include <Qt5GStreamer/QGlib/Connect>
#include <Qt5GStreamer/QGlib/Error>
#include <Qt5GStreamer/QGst/Init>
#include <Qt5GStreamer/QGst/Pipeline>
#include <Qt5GStreamer/QGst/ElementFactory>
#include <Qt5GStreamer/QGst/Pad>
#include <Qt5GStreamer/QGst/Structure>
#include <Qt5GStreamer/QGst/Bus>
#include <Qt5GStreamer/QGst/Message>
#include <Qt5GStreamer/QGst/Ui/VideoWidget>

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
	void onRtpBinPadAdded(const QGst::PadPtr & pad);
	void onBusErrorMessage(const QGst::MessagePtr & msg);
	void lala();

protected:
	virtual void resizeEvent(QResizeEvent *event);
	QUdpSocket *socket;

	QGst::PipelinePtr pipeline;
	QGst::Ui::VideoWidget *videoWidget;
	QGst::ElementPtr output;

	Hud *hud;
	int retryCount;
	bool retryEnable;
	QTimer *retryTimer;
	QTimer *xxtimer;

};
