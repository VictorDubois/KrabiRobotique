#ifndef ROUE_H
#define ROUE_H
#ifdef ROBOTHW
#include "constantes.h"
#ifdef STM32F40_41xxx
    #include "stm32f4xx_gpio.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_gpio.h"
#endif
#include "moteur.h"

class Roue : public Moteur
{
    private:

        GPIO_TypeDef * GPIOx_Sens;

        uint16_t GPIO_Pin_Sens;

        //bool oppositeDirection;

    public:
        Roue(TIM_TypeDef* TIMx, unsigned char OCx, GPIO_TypeDef* GPIOx_pwm, uint16_t GPIO_Pin_pwm, GPIO_TypeDef* GPIOx_Sens, uint16_t GPIO_Pin_Sens);
        //Roue(TIM_TypeDef* TIMx, unsigned char OCx, GPIO_TypeDef* GPIOx_pwm, uint16_t GPIO_Pin_pwm, GPIO_TypeD
             //Roue(TIM_TypeDef* TIMx, unsigned char OCx, GPIO_TypeDef* GPIOx_pwm, uint16_t GPIO_Pin_pwm, GPIO_TypeDef* GPIOx_Sens, uint16_t GPIO_Pin_Sens, bool oppositeDirection = false);

        void tourne(float rapport);
};
#endif
#endif // ROUE_H
