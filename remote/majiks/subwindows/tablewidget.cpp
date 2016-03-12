#include "tablewidget.h"

#include "serialproxy/abstractserialproxy.h"
#include "loggerwidget.h"

#include <cmath>

#include <QPainter>
#include <QFont>
#include <QPaintEvent>
#include <QDebug>
#include <QtGlobal>

TableWidget::TableWidget(AbstractSerialProxy *serialProxy, QWidget* parent): QWidget(parent),
TABLE_LENGTH(3000), TABLE_WIDTH(2000)
{
    m_serialProxy = serialProxy;

    setTableOrientation(false);
    setRobotVisible(true);
    setRobotAngle(0.f);
    setRobotPosition(QPointF(TABLE_LENGTH/4.f, 3.f*TABLE_WIDTH/4.f));
}

void TableWidget::setTableOrientation(bool rotated)
{
    m_tableIsRotated = rotated;
    update();
}

bool TableWidget::isTableRotated() const
{
    return m_tableIsRotated;
}

QPointF TableWidget::getOrientatedMaximaF() const
{
    return QPointF(getOrientatedMaxima());
}

QPoint TableWidget::getOrientatedMaxima() const
{
    if(isTableRotated())
        return QPoint(TABLE_WIDTH, TABLE_LENGTH);
    return QPoint(TABLE_LENGTH, TABLE_WIDTH);
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

float TableWidget::getRobotAngle() const
{
    return m_robotAngle;
}

void TableWidget::setRobotPosition(const QPointF& position)
{
    m_robotPosition.rx() = qBound<float>(0.f, position.x(), static_cast<float>(TABLE_LENGTH));
    m_robotPosition.ry() = qBound<float>(0.f, position.y(), static_cast<float>(TABLE_WIDTH));
    update();
}

QPointF TableWidget::getRobotPosition() const
{
    return m_robotPosition;
}

QPointF TableWidget::getRobotRelativePosition() const
{
    return QPointF(m_robotPosition.x()/static_cast<float>(TABLE_LENGTH), m_robotPosition.y()/static_cast<float>(TABLE_WIDTH));
}

void TableWidget::mouseDoubleClickEvent(QMouseEvent *evt)
{
    QPointF lw = getOrientatedMaximaF();
    float x = static_cast<float>(evt->x() * lw.x()) /(size().width());
    float y = static_cast<float>(evt->y() * lw.y()) /(size().height());

    if (evt->button() == Qt::LeftButton)
    {
        KrabiPacket p(KrabiPacket::RUN_GOTO);
        p.add(x);
        p.add(y);
        p.add(-1.f);

        qDebug() << "Sending robot to " << x << " " << y;

        m_serialProxy->sendData(p);
    }
}

void TableWidget::paintEvent(QPaintEvent *evt)
{
    QPointF lw = getOrientatedMaxima();

    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing, true);
    p.setWindow(QRect(0,0,lw.x(),lw.y()));
    p.setWorldMatrixEnabled(true);

    QFont font;
    font.setPixelSize(24);
    p.setFont(font);

    p.setOpacity(1);
    p.setPen(QColor(Qt::gray));
    p.fillRect(QRect(0, 0, lw.x(), lw.y()), QBrush(Qt::gray));

    // draw a grid
    // 100 mm
    p.setOpacity(0.25);
    p.setPen(QColor(Qt::white));

    for(unsigned int i=100; i<lw.x(); i+=100)
        p.drawLine(QPoint(i, 0), QPoint(i, lw.y()));
    for(unsigned int i=100; i<lw.y(); i+=100)
        p.drawLine(QPoint(0, i), QPoint(lw.x(), i));

    // 200 mm
    p.setOpacity(0.5);
    p.setPen(QColor(Qt::white));

    for(unsigned int i=0; i<lw.x(); i+=200)
    {
        p.setPen(QColor(Qt::white));
        p.drawLine(QPoint(i, 0), QPoint(i, lw.y()));
        p.setPen(QColor(Qt::black));
        p.drawText(QPoint(i + 16, 32), QString::number(i));
    }
    for(unsigned int i=0; i<lw.y(); i+=200)
    {
        p.setPen(QColor(Qt::white));
        p.drawLine(QPoint(0, i), QPoint(lw.x(), i));
        p.setPen(QColor(Qt::black));
        p.drawText(QPoint(16, i), QString::number(i));
    }

    // 1000 mm
    p.setOpacity(1);
    p.setPen(QColor(Qt::black));

    for(unsigned int i=1000; i<lw.x(); i+=1000)
        p.drawLine(QPoint(i, 0), QPoint(i, lw.y()));
    for(unsigned int i=1000; i<lw.y(); i+=1000)
        p.drawLine(QPoint(0, i), QPoint(lw.x(), i));

    // Robot
    if(isRobotVisible())
    {
        float r = 20.f; // Radius of the dot
        float l = r;    // Length of the dash

        p.setBrush(QColor(Qt::red));
        QPointF pos(getRobotPosition());
        if(isTableRotated())
        {
            pos.rx() = getRobotPosition().y();
            pos.ry() = getRobotPosition().x();
        }

        p.drawEllipse(pos, r, r);

        p.setPen(QColor(Qt::black));

        float c = cos(getRobotAngle()*3.14/180.f) * l;
        float s = sin(getRobotAngle()*3.14/180.f) * l;

        QPointF pos2(pos);

        if(!isTableRotated())
        {
            pos.rx() += c;
            pos.ry() += s;
        }
        else
        {
            pos.rx() += s;
            pos.ry() += c;
        }

        p.drawLine(pos, pos2);
    }

    evt->ignore();
}

