#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>

class AbstractSerialProxy;

class TableWidget: public QWidget
{
    public:
        TableWidget(AbstractSerialProxy *serialProxy, QWidget *parent = 0);

        void setRobotPosition(const QPointF& position);
        QPointF getRobotPosition() const;
        QPointF getRobotRelativePosition() const;
        void setRobotAngle(float angle);
        float getRobotAngle() const;

        void setRobotVisible(bool visible);
        bool isRobotVisible() const;

        void setTableOrientation(bool rotated);
        bool isTableRotated() const;

    protected:
        void paintEvent(QPaintEvent*);
        void mouseDoubleClickEvent(QMouseEvent*);

        QPoint getOrientatedMaxima() const;
        QPointF getOrientatedMaximaF() const;

    private:

        const unsigned int TABLE_LENGTH;
        const unsigned int TABLE_WIDTH;

        QPointF m_robotPosition;
        float   m_robotAngle;
        bool    m_robotVisible;

        bool    m_tableIsRotated;

        AbstractSerialProxy* m_serialProxy;
};

#endif // TABLEWIDGET_H
