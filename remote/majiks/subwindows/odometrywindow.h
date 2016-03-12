#ifndef OdometryWindow_H
#define OdometryWindow_H

#include <QWidget>

#include "../../../stm32/include/position.h"

namespace Ui {
class OdometryWindow;
}

class AbstractSerialProxy;

class OdometryWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit OdometryWindow(AbstractSerialProxy *serialProxy, QWidget *parent = nullptr);
        ~OdometryWindow();

        void setCurrentRobotPosition(QPointF position);
        void setCurrentRobotAngle(float angle);

        QPointF getRelativePosition() const;
        float getRelativeAngle() const;

        void settingsReceived(float wheelsize, float interaxis);

        void update();

        void requireSync();

    signals:
        void reseted();

    protected:
        void showEvent(QShowEvent* event);

    private:
        void resetReferences();

        void setWheelSizeFromX();
        void setWheelSizeFromY();
        void setInterAxisFromAngle();
        void apply();


        Ui::OdometryWindow *ui;

        QPointF m_currentRobotPosition;
        float   m_currentRobotAngle;

        QPointF m_referenceRobotPosition;
        float   m_referenceRobotAngle;

        AbstractSerialProxy* m_serialProxy;
};

#endif // OdometryWindow_H
