#ifndef BOUGIE_H_INCLUDED
#define BOUGIE_H_INCLUDED

#include <QColor>
#include <QObject>
#include <QPoint>
#include <QPainter>

class Bougie
{
    public:
        Bougie(const QColor& color = QColor(), const QPointF& position = QPointF(),  qreal radius = 0.0f);

        void draw(QPainter& painter);

        void setColor(const QColor& color);

        QPoint getPosition() const;

    private:
        QColor p_color;
        QPointF p_position;
        qreal p_radius;
};

#endif
