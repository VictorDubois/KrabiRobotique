#ifndef QUADRATURE_CODER_HANDLER_H_INCLUDED
#define QUADRATURE_CODER_HANDLER_H_INCLUDED

#include <stdint.h>
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

class QuadratureCoderHandler{
    private:
        TIM_TypeDef * coder_tim_port;

    public:
    QuadratureCoderHandler(TIM_TypeDef * coder_tim_port);
    int16_t getTickValue();
};


#endif // QUADRATURE_CODER_HANDLER_H_INCLUDED
