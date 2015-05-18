#include "hud.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <cmath>
#include <QFontDatabase>

#define aLineW 60
#define DEG(x) (x*180/M_PI)

Hud::Hud(QWidget *parent)
	: QWidget(parent), fov(50), psi(0), theta(0), phi(0), altitude(536)
{
	setPalette(Qt::transparent);
	setAttribute(Qt::WA_TransparentForMouseEvents);

	headingMark.moveTo(0, 0);
	headingMark.lineTo(3, -2);
	headingMark.lineTo(26, -2);
	headingMark.lineTo(26, 2);
	headingMark.lineTo(3, 2);
	headingMark.lineTo(0, 5);
	headingMark.lineTo(-3, 2);
	headingMark.lineTo(-26, 2);
	headingMark.lineTo(-26, -2);
	headingMark.lineTo(-3, -2);
	headingMark.closeSubpath();

	aLine.moveTo(aLineW, 4);
	aLine.lineTo(aLineW, 0);
	aLine.lineTo(24, 0);
	aLine.moveTo(-aLineW, 4);
	aLine.lineTo(-aLineW, 0);
	aLine.lineTo(-24, 0);

	cross.moveTo(-15, 0);
	cross.lineTo(15, 0);
	cross.moveTo(0, -15);
	cross.lineTo(0, 15);

	speedBox1.moveTo(-hw + 5, -80);
	speedBox1.lineTo(-hw + 50, -80);
	speedBox1.lineTo(-hw + 50, 120);
	speedBox1.lineTo(-hw + 5, 120);

	altBox1.moveTo(34, -100);
	altBox1.lineTo(0, -100);
	altBox1.lineTo(0, 100);
	altBox1.lineTo(34, 100);

	altBox2.moveTo(8, 0);
	altBox2.lineTo(13, 4);
	altBox2.lineTo(13, 10);
	altBox2.lineTo(45, 10);
	altBox2.lineTo(45, -10);
	altBox2.lineTo(13, -10);
	altBox2.lineTo(13, -4);
	altBox2.closeSubpath();
}

void Hud::setAH(float q0, float q1, float q2, float q3)
{
	phi = DEG(atan2(2 * (q0*q1 + q2*q3), 1 - 2 *(q1*q1 + q2*q2)));
	theta = DEG(asin(2 * (q0*q2 - q1*q3)));
	psi = DEG(atan2(2 * (q0*q3 + q1*q2), 1 - 2 *(q2*q2 + q3*q3)));
	  repaint();
}

void Hud::setEulers(int a, int b, int c)
{
	if (!((a >= -180) && (a <= 180) && (b >= -90) && (b <= 90) && (c >= -180) && (c <= 180)))
		return;
	psi = a;
	theta = b;
	phi = c;
	repaint();
}

void Hud::drawALines(QPainter& painter)
{
	painter.save();

	QFont font("Monospace");
	font.setPixelSize(8);
	painter.setFont(font);
	//painter.setClipRect(QRect(-hw + 50, -hh, (hw - 60) - (-hw + 50), h),Qt::ReplaceClip);

	painter.rotate(phi);
	painter.translate(0, h/fov*theta);

	for (int i = (theta - fov/2.0)/10; i <= (theta + fov/2.0)/10; i++) {
		painter.save();
		painter.translate(0, -h/(fov/10.0)*i);

		if (i < 0) {
			painter.setPen(QPen(Qt::green, 2, Qt::DashLine));
		} else {
			painter.setPen(QPen(Qt::green, 2, Qt::SolidLine));
		}

		int num = 10*i;
		if (abs(i) == 9) {
			painter.drawPath(cross);
		} else if (i > 0) {
			if (i > 9) num = 180 - 10*i;
			painter.drawText(68, -2, 15, 8, Qt::AlignLeft | Qt::AlignVCenter, \
					QString::number(num,10), 0);
			painter.drawText(-68 - 15, -2, 15, 8, Qt::AlignRight | Qt::AlignVCenter, \
					QString::number(num,10), 0);
			painter.drawPath(aLine);
		} else if (i < 0) {
			if (i < -9) num = -180 - 10*i;
			painter.drawText(68, -6, 15, 8, Qt::AlignLeft | Qt::AlignVCenter, \
					QString::number(num,10), 0);
			painter.drawText(-68 - 15, -6, 15, 8, Qt::AlignRight | Qt::AlignVCenter, \
					QString::number(num,10), 0);
			painter.scale(1, -1);
			painter.drawPath(aLine);
		} else {
			painter.drawLine(-100, 0, 100, 0);
		}

		painter.restore();
	}

	painter.restore();
}

void Hud::drawAltitude(QPainter& painter)
{
	painter.save();
	painter.translate(hw - 60, 20);

	painter.drawPath(altBox1);
	painter.drawPath(altBox2);

	painter.save();
	painter.setClipPath(altBox1 - altBox2);
	painter.translate(0, ((int)altitude % 5)*2.5);

	QFont font("Monospace");
	font.setPixelSize(8);
	painter.setFont(font);

	for (int i = 0; i < 6; i++) {
		painter.drawLine(0, i*25, 8, i*25);
		painter.drawText(10, -i*25 -4, 22, 8, Qt::AlignRight | Qt::AlignVCenter, QString::number(((int)altitude/5*5) + i*5, 10));

		painter.drawLine(0, -i*25, 8, -i*25);
		painter.drawText(10, i*25 -4, 22, 8, Qt::AlignRight | Qt::AlignVCenter, QString::number(((int)altitude/5*5) - i*5, 10));
	}
	painter.restore();

	font.setPixelSize(12);
	painter.setFont(font);

	painter.restore();

}

void Hud::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(width()/2, height()/2);
	painter.scale(width()/(double)w, height()/(double)h);
	painter.setPen(QPen(Qt::green, 1));
	painter.drawPath(headingMark);
	drawALines(painter);
	drawAltitude(painter);

	event->accept();
}
