#ifndef REMOTEWIDGET_H
#define REMOTEWIDGET_H

#include <QWidget>
#include <QPointF>

class QPushButton;
class QLabel;

class AbstractSerialProxy;

class RemoteWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit RemoteWidget(AbstractSerialProxy *serialProxy, QWidget *parent = nullptr);

        void setCurrentPosition(const QPointF& position, float angle);

        float getAngularStep()  const;
        float getLinearStep()   const;

        void setAngularStep (float step);
        void setLinearStep  (float step);

        void setSteps(float linearStep, float angularStep);

    private:
        void on_upButton_pressed();
        void on_downButton_pressed();
        void on_leftButton_pressed();
        void on_rightButton_pressed();

        void rotateRobot(float angle);
        void moveRobot(float distance);

        QPushButton* m_upButton;
        QPushButton* m_downButton;
        QPushButton* m_leftButton;
        QPushButton* m_rightButton;

        QLabel* m_currentPositionLabel;

        QPointF m_currentPosition;
        float m_currentAngle;

        float m_linearStep;
        float m_angularStep;

        AbstractSerialProxy* m_serialProxy;
};

#endif // REMOTEWIDGET_H
