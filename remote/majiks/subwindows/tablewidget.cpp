#include "tablewidget.h"

#include "bluetoothproxy/bluetoothproxy.h"
#include "loggerwidget.h"

#include <QPainter>
#include <QFont>
#include <QPaintEvent>
#include <QDebug>
#include <QtGlobal>

TableWidget::TableWidget(BluetoothProxy *bluetoothProxy, QWidget* parent): QWidget(parent),
TABLE_LENGTH(3000), TABLE_WIDTH(2000),
TABLE_LENGTH_F(static_cast<float>(TABLE_LENGTH)), TABLE_WIDTH_F(static_cast<float>(TABLE_WIDTH))
{
    m_bluetoothProxy = bluetoothProxy;

    setRobotVisible(true);
    setRobotAngle(0.f);
    setRobotPosition(QPointF(TABLE_LENGTH_F/2.f, TABLE_WIDTH_F/2.f));
}

void TableWidget::setRobotVisible(bool visible)
{
    m_robotVisible = visible;
}

bool TableWidget::isRobotVisible() const
{
    return m_robotVisible;
}

void TableWidget::setRobotAngle(float angle)
{
    m_robotAngle = angle;
    update();
}

void TableWidget::setRobotPosition(const QPointF& position)
{
    m_robotPosition.rx() = qBound<float>(0.f, position.x(), TABLE_LENGTH_F);
    m_robotPosition.ry() = qBound<float>(0.f, position.y(), TABLE_WIDTH_F);
    update();
}

QPointF TableWidget::getRobotPosition() const
{
    return m_robotPosition;
}

QPointF TableWidget::getRobotRelativePosition() const
{
    return QPointF(m_robotPosition.x()/TABLE_LENGTH_F, m_robotPosition.y()/TABLE_WIDTH_F);
}

void TableWidget::mouseDoubleClickEvent(QMouseEvent *evt)
{
    float x = static_cast<float>(evt->x() * TABLE_LENGTH_F)/(size().width());
    float y = static_cast<float>(evt->y() * TABLE_WIDTH_F) /(size().height());

    if (evt->button() == Qt::LeftButton)
    {
        KrabiPacket p(KrabiPacket::RUN_GOTO);
        p.add(x);
        p.add(y);
        p.add(-1.f);

        qDebug() << "Sending robot to " << x << " " << y;

        m_bluetoothProxy->sendData(p);
    }
}

void TableWidget::paintEvent(QPaintEvent *evt)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing, true);
    p.setWindow(QRect(0,0,TABLE_LENGTH,TABLE_WIDTH));
    p.setWorldMatrixEnabled(true);

    QFont font;
    font.setPixelSize(24);
    p.setFont(font);

    p.setOpacity(1);
    p.setPen(QColor(Qt::gray));
    p.fillRect(QRect(0, 0, TABLE_LENGTH, TABLE_WIDTH), QBrush(Qt::gray));

    // draw a grid
    // 100 mm
    p.setOpacity(0.25);
    p.setPen(QColor(Qt::white));

    for(unsigned int i=100; i<TABLE_LENGTH; i+=100)
        p.drawLine(QPoint(i, 0), QPoint(i, TABLE_WIDTH));
    for(unsigned int i=100; i<TABLE_WIDTH; i+=100)
        p.drawLine(QPoint(0, i), QPoint(TABLE_LENGTH, i));

    // 200 mm
    p.setOpacity(0.5);
    p.setPen(QColor(Qt::white));

    for(unsigned int i=0; i<TABLE_LENGTH; i+=200)
    {
        p.setPen(QColor(Qt::white));
        p.drawLine(QPoint(i, 0), QPoint(i, TABLE_WIDTH));
        p.setPen(QColor(Qt::black));
        p.drawText(QPoint(i + 16, 32), QString::number(i));
    }
    for(unsigned int i=0; i<TABLE_WIDTH; i+=200)
    {
        p.setPen(QColor(Qt::white));
        p.drawLine(QPoint(0, i), QPoint(TABLE_LENGTH, i));
        p.setPen(QColor(Qt::black));
        p.drawText(QPoint(16, i), QString::number(i));
    }

    // 1000 mm
    p.setOpacity(1);
    p.setPen(QColor(Qt::black));

    for(unsigned int i=1000; i<TABLE_LENGTH; i+=1000)
        p.drawLine(QPoint(i, 0), QPoint(i, TABLE_WIDTH));
    for(unsigned int i=1000; i<TABLE_WIDTH; i+=1000)
        p.drawLine(QPoint(0, i), QPoint(TABLE_LENGTH, i));

    // Robot
    if(isRobotVisible())
    {
        p.setBrush(QColor(Qt::red));
        p.drawEllipse(getRobotPosition(), 20.f, 20.f);
    }

    evt->ignore();
}

