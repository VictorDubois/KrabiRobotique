#include "timerHandler.h"

// Propage le signal de l’horloge système au timer.
void Timer::enableClock()
{
    switch(m_timer)
    {
        case 1:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
            break;
        case 2:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
            break;
        case 3:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
            break;
        case 4:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
            break;
    }
}

// Retourne le timer (TIM1, TIM2 ou TIM3), voir TIM_TypeDef.
TIM_TypeDef* Timer::getTIMx()
{
    switch(m_timer){
        case 1:
            return TIM1;
        case 2:
            return TIM2;
        case 3:
            return TIM3;
        case 4:
            return TIM4;
        default:
            return TIM4;
    }
}

Timer::Timer(uint8_t timer, uint16_t period, uint16_t prescaler, ClkDivision clockDivision)
{
    assert_param( timer > 0 && timer <= 4); //on vérifie que le timer entre 1 et 4
    m_timer = timer;
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
