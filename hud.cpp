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

#include "hud.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <cmath>
#include <QFontDatabase>

#define aLineW 60
#define DEG(x) (x*180/M_PI)

Hud::Hud(QWidget *parent)
	: QWidget(parent), fov(50), psi(0), theta(5), phi(60), altitude(1034.56)
{
	setPalette(Qt::transparent);
	setAttribute(Qt::WA_TransparentForMouseEvents);

	headingMark.moveTo(0, 0);
	headingMark.lineTo(3, -2);
	headingMark.lineTo(18, -2);
	headingMark.lineTo(18, 2);
	headingMark.lineTo(3, 2);
	headingMark.lineTo(0, 5);
	headingMark.lineTo(-3, 2);
	headingMark.lineTo(-18, 2);
	headingMark.lineTo(-18, -2);
	headingMark.lineTo(-3, -2);
	headingMark.closeSubpath();

	aLine.moveTo(aLineW, 4);
	aLine.lineTo(aLineW, 0);
	aLine.lineTo(22, 0);
	aLine.moveTo(-aLineW, 4);
	aLine.lineTo(-aLineW, 0);
	aLine.lineTo(-22, 0);

	cross.moveTo(-15, 0);
	cross.lineTo(15, 0);
	cross.moveTo(0, -15);
	cross.lineTo(0, 15);

	speedBox1.moveTo(-hw + 5, -80);
	speedBox1.lineTo(-hw + 50, -80);
	speedBox1.lineTo(-hw + 50, 120);
	speedBox1.lineTo(-hw + 5, 120);

	altBox1.moveTo(55, -100);
	altBox1.lineTo(0, -100);
	altBox1.lineTo(0, 100);
	altBox1.lineTo(55, 100);

	altBox2.moveTo(8, 0);
	altBox2.lineTo(13, 4);
	altBox2.lineTo(13, 10);
	altBox2.lineTo(55, 10);
	altBox2.lineTo(55, -10);
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
	QFont font("Crystal");
	font.setPixelSize(12);
	painter.setFont(font);
	painter.drawText(13, -13, 22, 26, Qt::AlignRight | Qt::AlignVCenter, \
			QString::number((int) altitude/100,10));
	font.setPixelSize(8);
	painter.setFont(font);
	painter.drawText(35, -13, 22, 26, Qt::AlignLeft | Qt::AlignVCenter, \
			QString::number(88,10));
	painter.drawText(35, -13 + 8, 22, 26, Qt::AlignLeft | Qt::AlignVCenter, \
			QString::number(88,10));
	painter.restore();

	//painter.drawPath(speedBox1);
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
