#include "mainwindow.h"
#include <QApplication>
#include <Qt5GStreamer/QGst/Init>
#include "quadgcs.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QGst::init(&argc, &argv);

	QuadGCS w;
	w.show();

	return a.exec();
}
