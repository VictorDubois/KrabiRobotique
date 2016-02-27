#include "graphwindow.h"

#include <QTimer>
#include <QVBoxLayout>
#include <QResizeEvent>

#include "graph.h"

GraphWindow::GraphWindow(QWidget *parent): QMainWindow(parent)
{
	QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GraphWindow::update);
    dt = 10;
	timer->start(dt);

	QWidget* inter = new QWidget(this);
	setCentralWidget(inter);

    inter->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

    graph = new Graph(inter);
}

void GraphWindow::update()
{
    graph->update();
}

void GraphWindow::resizeEvent(QResizeEvent* event)
{
    float proportion = static_cast<float>(graph->gWidth/graph->gHeight);

	QSize s = event->size();

	if(s.width() < s.height()*proportion)
		graph->resize(s.width(),s.width()/proportion);
	else
		graph->resize(proportion*s.height(),s.height());
}

