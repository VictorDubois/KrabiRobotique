#ifndef TIMER_HANDLER_H_INCLUDED
#define TIMER_HANDLER_H_INCLUDED

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

/**@brief Structure décrivant l’état d’un timer
 */
class Timer
{
public:
    enum ClkDivision ///< Facteur de division
    {
        Div1 = TIM_CKD_DIV1,
        Div2 = TIM_CKD_DIV2,
        Div4 = TIM_CKD_DIV4
    };

private:
    uint8_t m_timer;     ///< Numéro du timer
    uint16_t m_prescaler; ///< Facteur de division de l’horloge : @f$ fr\acute{e}quence du timer = \frac{72 MHz}{ timClockDivision (timPrescaler + 1)} @f$ .
    ClkDivision m_div; ///< Division d’horloge supplémentaire, voire Timer::ClkDivision.
    uint16_t m_period; ///< Période du timer.


    void enableClock() ///<Propage le signal de l’horloge système au timer.
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

public:
        TIM_TypeDef* getTIMx() ///< Retourne le timer (TIM1, TIM2 ou TIM3), voire TIM_TypeDef.
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
        //if(m_timer == 1)
        //    return TIM1;
        //return (TIM_TypeDef*)(0x40001400 - (m_timer-1)*0x400);
    }

    /**@brief Initialise le timer.
     * @param timer le numéro du timer (de 1 à 4).
     * @param period période du timer.
     * @param prescaler facteur de division de l’horloge : @f$ fr\acute{e}quence du timer = \frac{72 MHz}{ timClockDivision (timPrescaler + 1)} @f$ .
     * @param clockDivision : division d’horloge supplémentaire, voire Timer::ClkDivision.
     */
    Timer(uint8_t timer, uint16_t period, uint16_t prescaler, ClkDivision clockDivision)
    {
        assert_param( timer >= 0 && timer <= 4);
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

    /**@brief Retourne la période*/
    uint16_t getPeriod()
    {
        return m_period;
    }
};


#endif // TIMER_HANDLER_H_INCLUDED
