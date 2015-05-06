#include "simul/main_window.h"
#include "simul/table.h"
#include <QTimer>
#include <iostream>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QShortcut>
#include <QApplication>
#include <QStyle>
#include <QDebug>

MainWindow::MainWindow(bool isBlue)
{
	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	dt = 10;
	timer->start(dt);

    QWidget* inter = new QWidget(this);
	setCentralWidget(inter);

    inter->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

    table = new Table(this, inter, isBlue);

	this->setFixedSize(900,600);

    debugWindow = new DebugWindow(this);
    debugWindow->show();

    postStartTimer.start(1000);
    connect(&postStartTimer, SIGNAL(timeout()), this, SLOT(postStart()));
}

MainWindow::~MainWindow()
{
    delete debugWindow;
}

void MainWindow::update()
{
    table->update(dt);
}

DebugWindow* MainWindow::getDebugWindow()
{
    return debugWindow;
}

void MainWindow::postStart()
{
    debugWindow->setReady(true);
}

void MainWindow::mousePressEvent(QMouseEvent* evt)
{
    table->mousePressEvent(evt,true);
}

void MainWindow::keyPressEvent(QKeyEvent* evt)
{
	table->keyPressEvent(evt,true);
}

void MainWindow::keyReleaseEvent(QKeyEvent* evt)
{
    if (evt->key() == Qt::Key_Escape)
        exit(0);
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

void MainWindow::moveEvent(QMoveEvent * event)
{
    if (debugWindow->isAttached())
        debugWindow->moveWithoutEvent(this->mapToGlobal(QPoint()) + QPoint(this->width() + 16, -QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight)));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    debugWindow->close();
}

/// #include "main_window.moc"
