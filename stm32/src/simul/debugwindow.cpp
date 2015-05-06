#include "debugwindow.h"

#include <QDebug>
#include <QVBoxLayout>

DebugWindow::DebugWindow(MainWindow *parent) :
    QWidget(), parent(parent), attached(true), ready(false)
{
    this->setWindowTitle("Krabi Debug");
    setGeometry(0, 0, 240, 600);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);

    qlText = new QLabel(this);
    layout->addWidget(qlText);
}

bool DebugWindow::isAttached()
{
    return attached;
}

void DebugWindow::setReady(bool ready)
{
    this->ready = ready;
}

void DebugWindow::moveEvent(QMoveEvent * event)
{
    if (ready)
        attached = false;
}

void DebugWindow::moveWithoutEvent(QPoint pos)
{
    bool currentReady = ready;
    ready = false;

    move(pos);

    ready = currentReady;
}

void DebugWindow::setText(QString text)
{
    qlText->setText(text);
}
