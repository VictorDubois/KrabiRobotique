#include "brasTapis.h"

#ifdef ROBOTHW
BrasKrabi* BrasTapis::brasTapisLeft = 0;
BrasKrabi* BrasTapis::brasTapisRight = 0;
BrasTapis::BrasTapis()
{
//    #if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // Krabi Jr - STM32 H405 / STM32 H103
//        Timer* timer = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
//        TIM_CtrlPWMOutputs(TIM3, ENABLE);
//        this->brasTapisLeft = new BrasKrabi(timer, 1, 0.01f, 0.11f, 87.f, 51.f, 15.f);
//        this->brasTapisRight = new Bras(2timer, 3, 0.01f, 0.11f, 0.f, 40.f, 77.f);

//    #else // Krabi - STM32 H107
        Timer* timer = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
        TIM_CtrlPWMOutputs(TIM1, ENABLE);
        this->brasTapisLeft = new BrasKrabi(timer, 2, 0.01f, 0.11f, 20.f, 86.f, 84.f);
        this->brasTapisRight = new BrasKrabi(timer, 3, 0.01f, 0.11f, 120.f, 36.f, 1.f);

 //   #endif
    this->brasTapisLeft->collapse();
    this->brasTapisRight->collapse();
}

void BrasTapis::expand()
{
    this->brasTapisRight->expand();
    this->brasTapisLeft->expand();
}

void BrasTapis::collapse()
{
    this->brasTapisRight->collapse();
    this->brasTapisLeft->collapse();
}

BrasKrabi *BrasTapis::getRight()
{
    return brasTapisRight;
}

BrasKrabi *BrasTapis::getLeft()
{
    return this->brasTapisLeft;
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
