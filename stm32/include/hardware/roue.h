#ifndef ROUE_H
#define ROUE_H

#include "constantes.h"
#include "stm32f10x_gpio.h"
#include "moteur.h"

class Roue : public Moteur
{
    private:

        GPIO_TypeDef * GPIOx_Sens;

        uint16_t GPIO_Pin_Sens;

    public:

        Roue(TIM_TypeDef* TIMx, unsigned char OCx, GPIO_TypeDef* GPIOx_pwm, uint16_t GPIO_Pin_pwm, GPIO_TypeDef* GPIOx_Sens, uint16_t GPIO_Pin_Sens);

        void tourne(float rapport);
};

#endif // ROUE_H
