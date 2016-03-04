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

        void setRobotVisible(bool visible);
        bool isRobotVisible() const;

    protected:
        void paintEvent(QPaintEvent*);
        void mouseDoubleClickEvent(QMouseEvent*);

    private:

        const unsigned int TABLE_WIDTH;
        const unsigned int TABLE_LENGTH;

        const float TABLE_WIDTH_F;
        const float TABLE_LENGTH_F;

        QPointF m_robotPosition;
        bool m_robotVisible;

        BluetoothProxy* m_bluetoothProxy;
};

#endif // TABLEWIDGET_H
