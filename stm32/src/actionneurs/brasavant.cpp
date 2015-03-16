#include "brasavant.h"

#ifdef ROBOTHW
Bras2* BrasAvant::brasAvantLeft = 0;
Bras2* BrasAvant::brasAvantRight = 0;
BrasAvant::BrasAvant()
{
//    #if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // Krabi Jr - STM32 H405 / STM32 H103
//        Timer* timer = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
//        TIM_CtrlPWMOutputs(TIM3, ENABLE);
//        this->brasAvantLeft = new Bras2(timer, 1, 0.01f, 0.11f, 87.f, 51.f, 15.f);
//        this->brasAvantRight = new Bras(2timer, 3, 0.01f, 0.11f, 0.f, 40.f, 77.f);

//    #else // Krabi - STM32 H107
        Timer* timer = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
        TIM_CtrlPWMOutputs(TIM1, ENABLE);
        this->brasAvantLeft = new Bras2(timer, 2, 0.01f, 0.11f, 20.f, 86.f, 84.f);
        this->brasAvantRight = new Bras2(timer, 3, 0.01f, 0.11f, 120.f, 36.f, 1.f);

 //   #endif
    this->brasAvantLeft->collapse();
    this->brasAvantRight->collapse();
}

void BrasAvant::expand()
{
    this->brasAvantRight->expand();
    this->brasAvantLeft->expand();
}

void BrasAvant::collapse()
{
    this->brasAvantRight->collapse();
    this->brasAvantLeft->collapse();
}

Bras2 *BrasAvant::getRight()
{
    return brasAvantRight;
}

Bras2 *BrasAvant::getLeft()
{
    return this->brasAvantLeft;
}

#else

#include <QDebug>

    BrasAvant::BrasAvant()
    {}

    void BrasAvant::expand()
    {
#ifndef ROBOTHW
    qDebug() << "Bras devant sortis";
#endif
    }

    void BrasAvant::collapse()
    {
#ifndef ROBOTHW
    qDebug() << "Bras devant rentrés";
#endif
    }

#endif
