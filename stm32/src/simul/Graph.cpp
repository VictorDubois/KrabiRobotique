#include "simul/Graph.h"
#include "cstdlib"
#include "time.h"

#include <QWidget>
#include <iostream>
#include <QPainter>
#include "asservissement.h"

Graph::Graph(QWidget* widget) : QWidget(widget), vAngular(1000), vLinear(1000)
{
    dt=0;
	setAutoFillBackground(true);

	QPalette p = palette();
	p.setColor(QPalette::Window,QColor(Qt::darkGray));
	setPalette(p);
}
Graph::~Graph()
{

}

void Graph::update(int dt)
{
    this->dt = dt;
    repaint();
}
void Graph::paintEvent(QPaintEvent* evt)
{
    int diameter = 1;

    QPainter p(this);
	p.setRenderHints(QPainter::Antialiasing,true);
	p.setWindow(QRect(0,0,gWidth,gHeight));
	p.setWorldMatrixEnabled(true);

    vAngular.push_back(Asservissement::asservissement->getAngularSpeed());
    vLinear.push_back(Asservissement::asservissement->getLinearSpeed());


	p.fillRect(0,0,gWidth,gHeight,QColor(255,255,255));
	p.setPen(QColor(Qt::black));

	for (int i=0; i+1 < vLinear.size(); i++)
	{
        p.drawLine(i,-(gHeight/4)*(vLinear[i]/VITESSE_LINEAIRE_MAX)+gHeight/4,i+1,-(gHeight/4)*(vLinear[i+1]/VITESSE_LINEAIRE_MAX)+gHeight/4);
        //p.drawEllipse(QRectF(i -diameter / 2.0, (gHeight/2)*(vLinear[i]/VITESSE_LINEAIRE_MAX)+gHeight/2 -diameter / 2.0, diameter, diameter));
    }
    for (int i=0; i+1 < vLinear.size(); i++)
	{
        p.drawLine(i,-(gHeight/4)*(vAngular[i]/VITESSE_ANGULAIRE_MAX)+3*gHeight/4,i+1,-(gHeight/4)*(vAngular[i+1]/VITESSE_ANGULAIRE_MAX)+3*gHeight/4);
        //p.drawEllipse(QRectF(i -diameter / 2.0, (gHeight/2)*(vLinear[i]/VITESSE_LINEAIRE_MAX)+gHeight/2 -diameter / 2.0, diameter, diameter));
    }

}


void Graph::keyPressEvent(QKeyEvent* evt, bool press)
{

}



