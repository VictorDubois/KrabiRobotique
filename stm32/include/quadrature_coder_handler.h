#ifndef QUADRATURE_CODER_HANDLER_H_INCLUDED
#define QUADRATURE_CODER_HANDLER_H_INCLUDED

#include <stdint.h>
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

/**@brief Classe permettant de connaitre le nombre de tick des roue codeuses */
class QuadratureCoderHandler{
    private:
        /**@brief On utilise un timer pour cela */
        TIM_TypeDef * coder_tim_port;

    public:
        /**@brief Constructeur en spécifiant le timer */
        QuadratureCoderHandler(TIM_TypeDef * coder_tim_port);
        /**@brief Permet de connaitre le nombre de tick depuis le dernier appel de cette fonction*/
        int16_t getTickValue();
};


#endif // QUADRATURE_CODER_HANDLER_H_INCLUDED
