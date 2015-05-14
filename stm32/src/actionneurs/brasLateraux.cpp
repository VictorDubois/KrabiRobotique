#include "brasLateraux.h"

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
        if (right != 0 || left != 0)
            return;
        #if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // Krabi Jr - STM32 H405 / STM32 H103
            Timer* timer = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
            TIM_CtrlPWMOutputs(TIM3, ENABLE);

            left = new BrasLateraux(timer, 1, 0.01f, 0.11f, 87.f, 51.f, 15.f);
            right = new BrasLateraux(timer, 3, 0.01f, 0.11f, 0.f, 40.f, 77.f);
        #else // Krabi - STM32 H107
            Timer* timer = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
            TIM_CtrlPWMOutputs(TIM1, ENABLE);

            right = new BrasLateral(timer, 2, 0.01f, 0.11f, 96.f, 20.f, 84.f);
            left = new BrasLateral(timer, 3, 0.01f, 0.11f, 81.f, 180.f, 1.f);


        #endif

        left->collapse();
        right->collapse();
    }
#else


    BrasLateral::BrasLateral(){}

    void BrasLateral::expand(){} //sort les bras

    void BrasLateral::collapse(){} //ferme les bras

    void BrasLateral::front(){} //sort les bras a 80°

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
    initBrasLateraux();

    return left;
}

BrasLateral* BrasLateraux::getRight()
{
    initBrasLateraux();

    return right;
}

