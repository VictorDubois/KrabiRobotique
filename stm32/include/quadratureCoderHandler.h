#ifndef QUADRATURECODERHANDLER_H
#define QUADRATURECODERHANDLER_H

#ifdef ROBOTHW
#include <stdint.h>
#include "stm32f10x_tim.h"

/// @brief Classe permettant de connaitre le nombre de ticks des roues codeuses
class QuadratureCoderHandler
{
    private:

        /// @brief On utilise un timer pour cela
        TIM_TypeDef* coder_tim_port;

    public:

        /// @brief Constructeur en spécifiant le timer
        QuadratureCoderHandler(TIM_TypeDef* tim);

        /// @brief Permet de connaitre le nombre de ticks depuis le dernier appel de cette fonction
        int16_t getTickValue();
};

#endif // ROBOTHW

#endif // QUADRATURECODERHANDLER_H
