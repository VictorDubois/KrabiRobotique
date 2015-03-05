#include "moteur.h"

#include "constantes.h"
#include "timerHandler.h"
#ifdef STM32F40_41xxx
    #include "stm32f4xx_gpio.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_gpio.h"
#endif

Moteur::Moteur(TIM_TypeDef* TIMx, unsigned char OCx, GPIO_TypeDef* GPIOx_pwm, uint16_t GPIO_Pin_pwm)
    : pwm(new Timer(TIMx, PERIOD_TIMER_MOTEUR, PRESCALER_TIMER_MOTEUR, CLOCK_TIMER_MOTEUR), OCx)
{
    GPIO_InitTypeDef GPIO_InitStructureSortie;
    GPIO_InitStructureSortie.GPIO_Pin = GPIO_Pin_pwm;
    #ifdef STM32F40_41xxx
        GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructureSortie.GPIO_OType = GPIO_OType_PP;
    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_AF_PP;
    #endif
    GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx_pwm, &GPIO_InitStructureSortie);
}

void Moteur::tourne(float rapport)
{
    pwm.setDutyCycle(rapport);
}
