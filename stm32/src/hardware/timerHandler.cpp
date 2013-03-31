#include "timerHandler.h"

// Propage le signal de l’horloge système au timer.
void Timer::enableClock()
{
    if (m_TIMx == TIM1)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    else if (m_TIMx == TIM2)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    else if (m_TIMx == TIM3)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    else if (m_TIMx == TIM4)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    else if (m_TIMx == TIM5)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
}

// Retourne le timer (TIM1, TIM2 ou TIM3), voir TIM_TypeDef.
TIM_TypeDef* Timer::getTIMx()
{
    return m_TIMx;
}

Timer::Timer(TIM_TypeDef* TIMx, uint16_t period, uint16_t prescaler, ClkDivision clockDivision)
{
    m_TIMx = TIMx;
    m_period = period;
    m_prescaler = prescaler;
    m_div = clockDivision;

    enableClock();

    TIM_TimeBaseInitTypeDef timInit;
    timInit.TIM_Prescaler = prescaler;
    timInit.TIM_CounterMode = TIM_CounterMode_Up;
    timInit.TIM_Period = period;
    timInit.TIM_ClockDivision = clockDivision;
    timInit.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(getTIMx(), &timInit);
}

uint16_t Timer::getPeriod()
{
    return m_period;
}

void Timer::enableTimerClock(TIM_TypeDef* TIMx)
{
    if (TIMx == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }
    else if (TIMx == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }
    else if (TIMx == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    }
    else if (TIMx == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    }
    else if (TIMx == TIM5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    }
    else if (TIMx == TIM6)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    }
    else if (TIMx == TIM7)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    }
}
