#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>

class BluetoothProxy;

class TableWidget: public QWidget
{
    public:
        TableWidget(BluetoothProxy *bluetoothProxy, QWidget *parent = 0);

        void setRobotPosition(const QPointF& position);
        QPointF getRobotPosition() const;
        QPointF getRobotRelativePosition() const;
        void setRobotAngle(float angle);
        float getRobotAngle() const;

        void setRobotVisible(bool visible);
        bool isRobotVisible() const;

    protected:
        void paintEvent(QPaintEvent*);
        void mouseDoubleClickEvent(QMouseEvent*);

    private:

        const unsigned int TABLE_LENGTH;
        const unsigned int TABLE_WIDTH;

        const float TABLE_LENGTH_F;
        const float TABLE_WIDTH_F;


        QPointF m_robotPosition;
        float   m_robotAngle;
        bool    m_robotVisible;

        BluetoothProxy* m_bluetoothProxy;
};

#endif // TABLEWIDGET_H
