#include "brasLateraux.h"

BrasLateraux* BrasLateraux::left = 0;
BrasLateraux* BrasLateraux::right = 0;

#ifdef ROBOTHW

    BrasLateraux::BrasLateraux(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded, float angleFront)
        : angleCollapsed(angleCollapsed), angleExpanded(angleExpanded), angleFront(angleFront)
    {
        servo = new Servo(timer, OCx, RC0degre, RC180degres);
    }

    void BrasLateraux::expand()
    {
        servo->goToAngle(angleExpanded);
    }

    void BrasLateraux::collapse()
    {
        servo->goToAngle(angleCollapsed);
    }

    void BrasLateraux::front()
    {
        servo->goToAngle(angleFront);
    }

    void BrasLateraux::initBrasLateraux()
    {
        #if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // Krabi Jr - STM32 H405 / STM32 H103
            Timer* timer = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
            TIM_CtrlPWMOutputs(TIM3, ENABLE);

            left = new BrasLateraux(timer, 1, 0.01f, 0.11f, 87.f, 51.f, 15.f);
            right = new BrasLateraux(timer, 3, 0.01f, 0.11f, 0.f, 40.f, 77.f);
        #else // Krabi - STM32 H107
            Timer* timer = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
            TIM_CtrlPWMOutputs(TIM1, ENABLE);

            right = new BrasLateraux(timer, 2, 0.01f, 0.11f, 20.f, 86.f, 84.f);
            left = new BrasLateraux(timer, 3, 0.01f, 0.11f, 120.f, 36.f, 1.f);


        #endif

        left->collapse();
        right->collapse();
    }
#else


    BrasLateraux::BrasLateraux(){}

    void BrasLateraux::expand(){} //sort les bras

    void BrasLateraux::collapse(){} //ferme les bras

    void BrasLateraux::front(){} //sort les bras a 80°

    void BrasLateraux::initBrasLateraux()
    {
        left = new BrasLateraux();
        right = new BrasLateraux();
    }

#endif

BrasLateraux* BrasLateraux::getLeft()
{
    if (left==0)
        initBrasLateraux();

    return left;
}

BrasLateraux* BrasLateraux::getRight()
{
    if (right==0)
        initBrasLateraux();

    return right;
}

