#include "container.h"

#define CONTAINER_ANGLE_OPEN 80.
#define CONTAINER_ANGLE_CLOSE 10.

Container* Container::singleton = 0;

Container* Container::getSingleton()
{
    if (singleton==0)
        singleton = new Container();

    return singleton;
}

Container::Container()
{
#ifdef ROBOTHW
    Timer* timer3 = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
    TIM_CtrlPWMOutputs(TIM3, ENABLE);

    servo = new Servo(timer3, 2, 0.01f, 0.11f);
    close();
#endif
}

void Container::open()
{
#ifdef ROBOTHW
    servo->goToAngle(CONTAINER_ANGLE_OPEN);
#else
    qDebug() << "Ouvre Conteneur";
#endif
}

void Container::close()
{
#ifdef ROBOTHW
    servo->goToAngle(CONTAINER_ANGLE_CLOSE);
#else
    qDebug() << "Ferme Conteneur";
#endif
}
