#ifndef PWMHANDLER_H
#define PWMHANDLER_H

#ifdef STM32F40_41xxx
    #include "stm32f4xx_tim.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_tim.h"
#endif

#include "timerHandler.h"

/// @brief Classe représentant un générateur de PWM.
class PWMHandler
{
    private:

        Timer* timer;
        uint8_t OCx;

    public:

        /**@brief Initialise un nouveau générateur de PWM sur la sortie @a OCx du timer @a TIMx.
         *
         * @param TIMx un des quatres timers : TIM1, TIM2, TIM3, TIM4 ;
         * @param OCx une des quatres sorties : 1,2,3 et 4.
         */
        PWMHandler(Timer* tim, unsigned char OCx);

        /**@brief Stoppe la génération de PWM et détruit le générateur de PWM*/
        ~PWMHandler();

        /**@brief Change le rapport cyclique
         *
         * @param dutyCycle : le nouveau rapport cyclique.
         */
        void setDutyCycle(float dutyCycle);

        /**@brief Change la taille de l’impulsion.
         * @param pulseWidth : la nouvelle taille.
         */
        void setPulseWidth(uint16_t pulseWidth);

};

#endif //PWMHANDLER_H
