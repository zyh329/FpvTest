#include "fpv.h"
#include <QDebug>
#include "mavlink/common/mavlink.h"

#define DEG(x) (x*180/M_PI)

Fpv::Fpv(QWidget *parent)
	: QWidget(parent), retryCount(0), retryEnable(true)
{
	socket = new QUdpSocket(this);
	socket->bind(QHostAddress::Any, 14560);
	connect(socket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));

	setFixedSize(1296, 730);
	//setFixedSize(640*2, 480*2);
	setContentsMargins(0, 0, 0, 0);

	videoWidget = new QGst::Ui::VideoWidget;
	videoWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	QLayout *layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(videoWidget);
	setLayout(layout);

	hud = new Hud(this);
	//hud->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	hud->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

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
	while (socket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(socket->pendingDatagramSize());
		socket->readDatagram(datagram.data(), datagram.size());

		mavlink_message_t msg;
		mavlink_status_t status;
		mavlink_attitude_t attitude;

		for (int i = 0; i < datagram.size(); ++i) {
			if (mavlink_parse_char(MAVLINK_COMM_0, datagram.data()[i], &msg, &status)) {
				switch (msg.msgid) {
				case MAVLINK_MSG_ID_ATTITUDE:
					mavlink_msg_attitude_decode(&msg, &attitude);
					//qDebug() << "pitch:" << attitude.pitch << "roll:" << attitude.roll << "yaw:" << attitude.yaw;
					hud->setEulers(DEG(attitude.yaw), DEG(attitude.pitch), DEG(attitude.roll));
					break;
				default:
					break;
				}
			}
		}

	}
}

void Fpv::startFpv()
{
	stopFpv();
	pipeline = QGst::Pipeline::create();

	QGst::ElementPtr rtpbin = QGst::ElementFactory::make("rtpbin");
	if (!rtpbin) {
		qFatal("Failed to create gstrtpbin");
	}
	rtpbin->setProperty("latency", 60);
	rtpbin->setProperty("drop-on-latency", true);
	pipeline->add(rtpbin);

	QGst::ElementPtr rtpudpsrc = QGst::ElementFactory::make("udpsrc");
	if (!rtpudpsrc) {
		qFatal("Failed to create udpsrc. Aborting...");
	}
	rtpudpsrc->setProperty("port", 5000);
	rtpudpsrc->setProperty("caps", QGst::Caps::fromString("application/x-rtp,"
														  "media=(string)video,"
														  "clock-rate=(int)90000,"
														  "encoding-name=(string)H264"));
	pipeline->add(rtpudpsrc);
	rtpudpsrc->link(rtpbin, "recv_rtp_sink_0");

	QGst::ElementPtr rtcpudpsrc = QGst::ElementFactory::make("udpsrc");
	rtcpudpsrc->setProperty("port", 5001);
	pipeline->add(rtcpudpsrc);
	rtcpudpsrc->link(rtpbin, "recv_rtcp_sink_0");

	QGst::ElementPtr rtcpudpsink = QGst::ElementFactory::make("udpsink");
	rtcpudpsink->setProperty("host", "192.168.13.1");
//	rtcpudpsink->setProperty("host", "127.0.0.1");
	rtcpudpsink->setProperty("port", 5005);
	rtcpudpsink->setProperty("sync", false);
	rtcpudpsink->setProperty("async", false);
	pipeline->add(rtcpudpsink);
	rtpbin->link("send_rtcp_src_0", rtcpudpsink);

	output = QGst::ElementFactory::make("qwidget5videosink");
	output->setProperty("sync", false);
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
		if (pad->name().startsWith(QLatin1String("recv_rtp_src_0"))) {
			bin = QGst::Bin::fromDescription(
					"rtph264depay ! avdec_h264 ! queue leaky=2 ! videoconvert");
			qDebug() << "added";
		}
	} catch (const QGlib::Error & error) {
		qCritical() << error;
		qFatal("One ore more required elements are missing. Aborting...");
	}

	pipeline->add(bin);
	bin->syncStateWithParent();
	pad->link(bin->getStaticPad("sink"));

	output->syncStateWithParent();
	bin->getStaticPad("src")->link(output->getStaticPad("sink"));
}

void Fpv::onBusErrorMessage(const QGst::MessagePtr & msg)
{
	qCritical() << "Error from bus:" << msg.staticCast<QGst::ErrorMessage>()->error();
	stopFpv();
	//TODO Restart only when the errror is "Internal data flow error".
	retryTimer->start(500);
}

void Fpv::lala()
{

}

void Fpv::resizeEvent(QResizeEvent *event)
{
	hud->resize(event->size());
	event->accept();
}
