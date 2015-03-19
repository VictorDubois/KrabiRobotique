#include "brasTapis.h"

#ifdef ROBOTHW
BrasTapis* BrasTapis::brasTapisLeft = 0;
BrasTapis* BrasTapis::brasTapisRight = 0;

BrasTapis::BrasTapis(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded):BrasKrabi(timer, OCx, RC0degre, RC180degres, angleCollapsed, angleExpanded, 0.f)
{}

void BrasTapis::initBrasTapis()
{
//    #if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // Krabi Jr - STM32 H405 / STM32 H103
//        Timer* timer = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
//        TIM_CtrlPWMOutputs(TIM3, ENABLE);
//        this->brasTapisLeft = new BrasTapis(timer, 1, 0.01f, 0.11f, 87.f, 51.f);
//        this->brasTapisRight = new BrasTapis(2timer, 3, 0.01f, 0.11f, 0.f, 40.f);

//    #else // Krabi - STM32 H107
        Timer* timer = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
        TIM_CtrlPWMOutputs(TIM1, ENABLE);
        brasTapisLeft = new BrasTapis(timer, 2, 0.01f, 0.11f, 20.f, 86.f);
        brasTapisRight = new BrasTapis(timer, 3, 0.01f, 0.11f, 120.f, 36.f);

 //   #endif
    brasTapisLeft->collapse();
    brasTapisRight->collapse();
}

void BrasTapis::expand()
{
    brasTapisRight->expand();
    brasTapisLeft->expand();
}

void BrasTapis::collapse()
{
    brasTapisRight->collapse();
    brasTapisLeft->collapse();
}

BrasTapis *BrasTapis::getRight()
{
    if (brasTapisRight == 0)
        initBrasTapis();
    return brasTapisRight;
}

BrasTapis *BrasTapis::getLeft()
{
    if (brasTapisLeft == 0)
        initBrasTapis();
    return brasTapisLeft;
}

#else

#include <QDebug>

    BrasTapis::BrasTapis()
    {}

    void BrasTapis::expand()
    {
#ifndef ROBOTHW
    qDebug() << "Bras devant sortis";
#endif
    }

    void BrasTapis::collapse()
    {
#ifndef ROBOTHW
    qDebug() << "Bras devant rentrés";
#endif
    }

#endif
