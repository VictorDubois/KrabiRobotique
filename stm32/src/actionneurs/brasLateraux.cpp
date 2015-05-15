#include "brasLateraux.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

BrasLateral* BrasLateraux::left = 0;
BrasLateral* BrasLateraux::right = 0;

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

    void BrasLateraux::initBrasLateraux()
    {
        #if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // Krabi Jr - STM32 H405 / STM32 H103
            Timer* timer = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
            TIM_CtrlPWMOutputs(TIM3, ENABLE);

            right = new BrasLateral(timer, 2, 0.01f, 0.11f, 96.f, 20.f, 84.f);
            left = new BrasLateral(timer, 3, 0.01f, 0.11f, 81.f, 180.f, 1.f);
        #else // Krabi - STM32 H107
            Timer* timer = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
            TIM_CtrlPWMOutputs(TIM1, ENABLE);

            right = new BrasLateral(timer, 2, 0.01f, 0.11f, 96.f, 0.f, 84.f);
            left = new BrasLateral(timer, 3, 0.01f, 0.11f, 81.f, 181.f, 1.f);


        #endif

        left->collapse();
        right->expand();
    }
#else


    BrasLateral::BrasLateral(){}

    void BrasLateral::expand(){qDebug() << "On ouvre le bras";} //sort les bras

    void BrasLateral::collapse(){qDebug() << "On ferme le bras";} //ferme les bras

    void BrasLateral::front(){qDebug() << "On positionne le bras à l'angle front";} //sort les bras a 80°

    void BrasLateraux::initBrasLateraux()
    {
        if (right != 0 || left != 0)
            return;

        left = new BrasLateral();
        right = new BrasLateral();
    }

#endif

BrasLateral* BrasLateraux::getLeft()
{
    if (right == 0 && left == 0)
        initBrasLateraux();

    return left;
}

BrasLateral* BrasLateraux::getRight()
{
    if (right == 0 && left == 0)
        initBrasLateraux();

    return right;
}
