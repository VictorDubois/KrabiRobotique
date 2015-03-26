#include "braslateral.h"

BrasLateral* BrasLateral::left = 0;
BrasLateral* BrasLateral::right = 0;

#ifdef ROBOTHW

    BrasLateral::BrasLateral(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded, float angleFront)
        : angleCollapsed(angleCollapsed), angleExpanded(angleExpanded), angleFront(angleFront)
    {
        servo = new Servo(timer, OCx, RC0degre, RC180degres);
    }

    void BrasLateral::expand()
    {
        servo->goToAngle(angleExpanded);
    }

    void BrasLateral::collapse()
    {
        servo->goToAngle(angleCollapsed);
    }

    void BrasLateral::front()
    {
        servo->goToAngle(angleFront);
    }

    void BrasLateral::initBrasLateraux()
    {
        #if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // Krabi Jr - STM32 H405 / STM32 H103
            Timer* timer = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
            TIM_CtrlPWMOutputs(TIM3, ENABLE);

            left = new BrasLateral(timer, 1, 0.01f, 0.11f, 87.f, 51.f, 15.f);
            right = new BrasLateral(timer, 3, 0.01f, 0.11f, 0.f, 40.f, 77.f);
        #else // Krabi - STM32 H107
            Timer* timer = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
            TIM_CtrlPWMOutputs(TIM1, ENABLE);

            right = new BrasLateral(timer, 2, 0.01f, 0.11f, 20.f, 86.f, 84.f);
            left = new BrasLateral(timer, 3, 0.01f, 0.11f, 120.f, 36.f, 1.f);


        #endif

        left->collapse();
        right->collapse();
    }
#else

#include <QDebug>

    BrasLateral::BrasLateral()
    {}

    void BrasLateral::expand()
    {
#ifndef ROBOTHW
    qDebug() << "Bras lateral sorti";
#endif
    }

    void BrasLateral::collapse()
    {
#ifndef ROBOTHW
    qDebug() << "Bras Lateral rentré";
#endif
    }

    void BrasLateral::front()
    {
#ifndef ROBOTHW
    qDebug() << "Bras Lateral sorti à 180°";
#endif
    }

    void BrasLateral::initBrasLateraux()
    {
        left = new BrasLateral();
        right = new BrasLateral();
    }

#endif

BrasLateral* BrasLateral::getLeft()
{
    if (left==0)
        initBrasLateraux();

    return left;
}

BrasLateral* BrasLateral::getRight()
{
    if (right==0)
        initBrasLateraux();

    return right;
}

