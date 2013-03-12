#include "bougie.h"


Bougie::Bougie(const QColor& color, const QPointF& position, qreal radius)
{
    p_color = color;
    p_radius = radius;
    p_position = position;
}

void Bougie::draw(QPainter& painter)
{
    painter.setBrush(p_color);
    painter.setPen(p_color);
    painter.drawEllipse(p_position, p_radius, p_radius);
}

void Bougie::setColor(const QColor& color)
{
    p_color = color;
}

QPoint Bougie::getPosition() const
{
    return QPoint(p_position.x(), p_position.y());
}
