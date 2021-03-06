#ifndef TIMERHANDLER_H
#define TIMERHANDLER_H
#ifdef ROBOTHW
#ifdef STM32F40_41xxx
    #include "stm32f4xx_tim.h"
    #include "stm32f4xx_rcc.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_tim.h"
    #include "stm32f10x_rcc.h"
#endif

/// @brief Structure décrivant l’état d’un timer
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

        TIM_TypeDef* m_TIMx;
        uint16_t m_prescaler; ///< Facteur de division de l’horloge : @f$ fr\acute{e}quence du timer = \frac{72 MHz}{ timClockDivision (timPrescaler + 1)} @f$ .
        ClkDivision m_div; ///< Division d’horloge supplémentaire, voir Timer::ClkDivision.
        uint16_t m_period; ///< Période du timer.

        void enableClock(); ///<Propage le signal de l’horloge système au timer.

    public:

        TIM_TypeDef* getTIMx(); ///< Retourne le timer (TIM1, TIM2, TIM3 ou TIM4), voire TIM_TypeDef.

        /**@brief Initialise le timer.
        * @param timer le numéro du timer (de 1 à 4).
        * @param period période du timer.
        * @param prescaler facteur de division de l’horloge : @f$ fr\acute{e}quence du timer = \frac{72 MHz}{ timClockDivision (timPrescaler + 1)} @f$ .
        * @param clockDivision : division d’horloge supplémentaire, voire Timer::ClkDivision.
        */
        Timer(TIM_TypeDef* TIMx, uint16_t period, uint16_t prescaler, ClkDivision clockDivision);

        /// @brief Retourne la période
        uint16_t getPeriod();

        // Active un timer
        static void enableTimerClock(TIM_TypeDef* TIMx);
};

#endif
#endif // TIMERHANDLER_H
