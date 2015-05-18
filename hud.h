#pragma once
#include <QWidget>
#include <QPainter>

class Hud : public QWidget
{
	Q_OBJECT

public:
	Hud(QWidget *parent = 0);
	bool hasHeightForWidth() const override { return true; }
	int heightForWidth(int w) const override { return w*4/3; }

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
	static const int w = 640;
	static const int h = 480;
	static const int hw = w/2;
	static const int hh = h/2;

private:
	Q_DISABLE_COPY(Hud);
};
