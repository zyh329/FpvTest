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

#ifndef HUD_H_
#define HUD_H_

#include <QWidget>
#include <QPainter>

class Hud : public QWidget
{
	Q_OBJECT

public:
	Hud(QWidget *parent = 0);
	void setFov(int _fov) { fov = _fov; }
	void setEulers(int a, int b, int c);
	void setAH(float q0, float q1, float q2, float q3);
	void setAltitude(double alt) { altitude =  alt; }

protected:
	virtual void paintEvent(QPaintEvent *event);
	void drawALines(QPainter& painter);
	void drawAltitude(QPainter& painter);
	QPainterPath headingMark;
	QPainterPath aLine;
	QPainterPath cross;
	QPainterPath altBox1;
	QPainterPath altBox2;
	QPainterPath speedBox1;
	int fov;
	int psi;	//!< First Euler angle.
	int theta;	//!< Second Euler angle.
	int phi;	//!< Third Euler angle.
	double altitude;
	static const int w = 400;
	static const int h = 300;
	static const int hw = w/2;
	static const int hh = h/2;

private:
	Q_DISABLE_COPY(Hud);
};

#endif /* HUD_H_ */
