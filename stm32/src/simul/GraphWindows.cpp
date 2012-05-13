#include "simul/GraphWindows.h"
#include <QTimer>
#include <iostream>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "simul/Graph.h"

GraphWindows::GraphWindows()
{
	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    dt = 10;
	timer->start(dt);

	QWidget* inter = new QWidget(this);
	setCentralWidget(inter);

    inter->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

    graph = new Graph(inter);
}

GraphWindows::~GraphWindows()
{
}

void GraphWindows::update()
{
    graph->update(dt);
}

void GraphWindows::resizeEvent(QResizeEvent* event)
{
	float proportion = (float) graph->gWidth/graph->gHeight;

	QSize s = event->size();

	if(s.width() < s.height()*proportion)
		graph->resize(s.width(),s.width()/proportion);
	else
		graph->resize(proportion*s.height(),s.height());
}

#include "GraphWindows.moc"
