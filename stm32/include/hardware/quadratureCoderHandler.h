#ifndef QUADRATURECODERHANDLER_H
#define QUADRATURECODERHANDLER_H

#ifdef ROBOTHW
#include <stdint.h>
#include "stm32f10x_tim.h"

/// @brief Classe permettant de connaitre le nombre de ticks des roues codeuses
class QuadratureCoderHandler
{
    private:

        /// @brief Le timer des roues codeuses
        TIM_TypeDef* coder_tim_port;

    public:

        /// @brief Constructeur en spécifiant le timer et les pins des 2 channels
        /// GPIO_ch1 et pin_Ch1 : pour la pin du channel 1 du timer
        /// GPIO_ch2 et pin_Ch2 : pour la pin du channel 2 du timer
        QuadratureCoderHandler(TIM_TypeDef* TIMx, GPIO_TypeDef* GPIO_ch1, uint16_t pin_Ch1, GPIO_TypeDef* GPIO_ch2, uint16_t pin_Ch2);

        /// @brief Permet de connaitre le nombre de ticks depuis le dernier appel de cette fonction
        int16_t getTickValue();
};

#endif // ROBOTHW

#endif // QUADRATURECODERHANDLER_H
