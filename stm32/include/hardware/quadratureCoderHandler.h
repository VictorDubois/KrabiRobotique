#ifndef QUADRATURECODERHANDLER_H
#define QUADRATURECODERHANDLER_H

#ifdef ROBOTHW
#include <stdint.h>
#ifdef STM32F40_41xxx
    #include "stm32f4xx_tim.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_tim.h"
#endif

/// @brief Classe permettant de connaitre le nombre de ticks des roues codeuses
class QuadratureCoderHandler
{
    private:

        /// @brief On utilise un timer pour cela
        TIM_TypeDef* coder_tim_port;
        void initCoder();

    public:

        /// @brief Constructeur en spécifiant le timer et les pins des 2 channels
        /// GPIO_ch1 et pin_Ch1 : pour la pin du channel 1 du timer
        /// GPIO_ch2 et pin_Ch2 : pour la pin du channel 2 du timer
        QuadratureCoderHandler(TIM_TypeDef* TIMx, GPIO_TypeDef* GPIO_ch1, uint16_t pin_Ch1, GPIO_TypeDef* GPIO_ch2, uint16_t pin_Ch2,
                               uint8_t TIMx_AF = 0, uint8_t pinSource_Ch1 = 0, uint8_t pinSource_Ch2 = 0);

        /// @brief Permet de connaitre le nombre de ticks depuis le dernier appel de cette fonction
        int16_t getTickValue();
};

#endif // ROBOTHW

#endif // QUADRATURECODERHANDLER_H
