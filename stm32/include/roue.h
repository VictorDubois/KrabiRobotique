#ifndef ROUE_H_INCLUDED
#define ROUE_H_INCLUDED

#include "variable.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "timer_handler.h"
#include "Moteur.h"
#include <math.h>
#include <float.h>

class Roue : public Moteur{
    private:
        GPIO_TypeDef * GPIOx_Sens;
        uint16_t GPIO_Pin_Sens;
    public:
        Roue(unsigned char OCx, GPIO_TypeDef * GPIOx_Sens, uint16_t GPIO_Pin_Sens);
        void tourne(float rapport);
};

#endif // ROUE_H_INCLUDED
