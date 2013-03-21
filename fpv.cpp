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

#include "fpv.h"
#include <QDebug>

Fpv::Fpv(QWidget *parent)
	: QWidget(parent), retryCount(0), retryEnable(true)
{
	socket = new QUdpSocket(this);
	socket->bind(QHostAddress::Any, 12345);
	connect(socket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));

	setFixedSize(1024, 768);
	setContentsMargins(0, 0, 0, 0);

	videoWidget = new QGst::Ui::VideoWidget;
	videoWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	QLayout *layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(videoWidget);
	setLayout(layout);

	hud = new Hud(this);
	hud->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	retryTimer = new QTimer(this);
	retryTimer->setSingleShot(true);
	connect(retryTimer, SIGNAL(timeout()), this, SLOT(startFpv()));
	retryTimer->start(500);
}

Fpv::~Fpv()
{
	stopFpv();
}

void Fpv::readDatagrams()
{
	float q[4];
	while (socket->hasPendingDatagrams()) {
		socket->readDatagram(reinterpret_cast<char *>(q), 16);
		hud->setAH(q[0], q[1], q[2], q[3]);
		qDebug() << q[0] << endl;
	}
}

void Fpv::startFpv()
{
	stopFpv();
	pipeline = QGst::Pipeline::create();

	QGst::ElementPtr rtpbin = QGst::ElementFactory::make("gstrtpbin");
    if (!rtpbin) {
        qCritical("Failed to create gstrtpbin");
        return;
    }
    rtpbin->setProperty("latency", 5);
    pipeline->add(rtpbin);

	QGst::ElementPtr rtpUdpSrc = QGst::ElementFactory::make("udpsrc");
	if (!rtpUdpSrc) {
		qFatal("Failed to create udpsrc. Aborting...");
	}
	rtpUdpSrc->setProperty("port", 5000);
	rtpUdpSrc->setProperty("caps", QGst::Caps::fromString("application/x-rtp,"
			"media=(string)video,"
			"clock-rate=(int)90000"));
	pipeline->add(rtpUdpSrc);
	rtpUdpSrc->link(rtpbin, "recv_rtp_sink_0");

	QGst::ElementPtr rtcpudpsrc = QGst::ElementFactory::make("udpsrc");
	rtcpudpsrc->setProperty("port", 5001);
	pipeline->add(rtcpudpsrc);
	rtcpudpsrc->link(rtpbin, "recv_rtcp_sink_0");

	QGst::ElementPtr rtcpudpsink = QGst::ElementFactory::make("udpsink");
	//rtcpudpsink->setProperty("host", "127.0.0.1");
	rtcpudpsink->setProperty("host", "192.168.3.1");
	rtcpudpsink->setProperty("port", 5005);
	rtcpudpsink->setProperty("sync", false);
	rtcpudpsink->setProperty("async", false);
	pipeline->add(rtcpudpsink);
	rtpbin->link("send_rtcp_src_0", rtcpudpsink);

	output = QGst::ElementFactory::make("qwidgetvideosink");
	videoWidget->setVideoSink(output);
	pipeline->add(output);

	QGlib::connect(rtpbin, "pad-added", this, &Fpv::onRtpBinPadAdded);

	pipeline->bus()->addSignalWatch();
	QGlib::connect(pipeline->bus(), "message::error", this, &Fpv::onBusErrorMessage);

	pipeline->setState(QGst::StatePlaying);
}

void Fpv::stopFpv()
{
	if (pipeline) {
		pipeline->setState(QGst::StateNull);
		pipeline.clear();
	}

	if (output) {
		output->setState(QGst::StateNull);
		output.clear();
	}

	if (videoWidget->videoSink()) {
		videoWidget->releaseVideoSink();
	}
}

void Fpv::onRtpBinPadAdded(const QGst::PadPtr & pad)
{
	QGst::ElementPtr bin;

	try {
		if (pad->caps()->internalStructure(0)->value("media").toString() == QLatin1String("video")) {
			bin = QGst::Bin::fromDescription(
					"rtpjpegdepay ! jpegdec ! ffmpegcolorspace");
		}
	} catch (const QGlib::Error & error) {
		qCritical() << error;
		qFatal("One ore more required elements are missing. Aborting...");
	}

	pipeline->add(bin);
	bin->syncStateWithParent();
	output->syncStateWithParent();

	pad->link(bin->getStaticPad("sink"));
	bin->getStaticPad("src")->link(output->getStaticPad("sink"));
}

void Fpv::onBusErrorMessage(const QGst::MessagePtr & msg)
{
	qCritical() << "Error from bus:" << msg.staticCast<QGst::ErrorMessage>()->error();
	stopFpv();
	//TODO Restart only when the errror is "Internal data flow error".
	retryTimer->start(500);
}

void Fpv::resizeEvent(QResizeEvent *event)
{
	hud->resize(event->size());
	event->accept();
}
