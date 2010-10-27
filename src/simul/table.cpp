#include "simul/table.h"
#include "simul/robot.h"
#include <iostream>
#include <QPainter>

Table::Table(QWidget* parent) : QWidget(parent)
{
	dt=0;
	setAutoFillBackground(true);
	
	QPalette p = palette();
	p.setColor(QPalette::Window,QColor(Qt::darkGray));
	setPalette(p);

	robots.push_back(new Robot());

	elements.push_back(new Element(Position(300,300),Element::Pion));
}

Table::~Table()
{
}

void Table::update(int dt)
{
	this->dt = dt;
	repaint();
}

void Table::paintEvent(QPaintEvent* evt)
{
	static float l = 0;
	l+= dt*0.005;
	QPainter p(this);
	p.setRenderHints(QPainter::Antialiasing,true);
	p.setWindow(QRect(0,0,tableWidth,tableHeight));
	p.setWorldMatrixEnabled(true);


	for(unsigned int i=0; i<6; i++)
	for(unsigned int j=0; j<6; j++)
		p.fillRect(450+i*350,j*350,350,350, ((i+j) & 1) ? Qt::red : Qt::blue);
	p.drawEllipse(QRectF(50.0,50.0f,100,l));
	//Starting zones
	p.fillRect(0,400,400,1700,QColor(0,146,54));
	p.fillRect(2600,400,400,1700,QColor(0,146,54));
	//Green zones
	p.fillRect(0,0,400,400,Qt::red);
	p.fillRect(2600,0,400,400,Qt::blue);
	//Starting zones borders
	p.fillRect(0,389,400,22,Qt::black);
	p.fillRect(2600,389,400,22,Qt::black);

	//Blocked zones
	p.fillRect(450,1980,700,120,Qt::black);
	p.fillRect(1850,1980,700,120,Qt::black);

	p.fillRect(450,1850,22,130,Qt::black);
	p.fillRect(1850,1850,22,130,Qt::black);

	p.fillRect(1128,1850,22,130,Qt::black);
	p.fillRect(2528,1850,22,130,Qt::black);


	p.setBrush(QBrush(QColor("yellow")));
	p.setPen(QBrush(QColor("yellow")));

	for(unsigned int i=0; i < elements.size(); i++)
		elements[i]->paint(p);

	for(unsigned int i=0; i < robots.size(); i++)
		robots[i]->paint(p,dt);

	dt = 0;
}

void Table::keyPressEvent(QKeyEvent* evt, bool press)
{
	for(unsigned int i=0; i < robots.size(); i++)
		robots[i]->keyPressEvent(evt, press);
}

