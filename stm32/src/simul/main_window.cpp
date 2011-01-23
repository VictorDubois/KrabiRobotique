#include "simul/main_window.h"
#include "simul/table.h"
#include <QTimer>
#include <iostream>
#include <QVBoxLayout>
#include <QResizeEvent>

MainWindow::MainWindow()
{
	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	dt = 10;
	timer->start(dt);

	QWidget* inter = new QWidget(this);
	setCentralWidget(inter);

inter->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

	table = new Table(inter);
}

MainWindow::~MainWindow()
{
}

void MainWindow::update()
{
	table->update(dt);
}

void MainWindow::keyPressEvent(QKeyEvent* evt)
{
	table->keyPressEvent(evt,true);
}

void MainWindow::keyReleaseEvent(QKeyEvent* evt)
{
	table->keyPressEvent(evt,false);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	float proportion = (float)table->tableWidth/table->tableHeight;

	QSize s = event->size();

	if(s.width() < s.height()*proportion)
		table->resize(s.width(),s.width()/proportion);
	else
		table->resize(proportion*s.height(),s.height());
}

#include "main_window.moc"
