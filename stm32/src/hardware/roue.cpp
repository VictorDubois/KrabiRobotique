#include "roue.h"

#include "stm32f10x_rcc.h"
#include <math.h>

Roue::Roue(TIM_TypeDef* TIMx, unsigned char OCx, GPIO_TypeDef * GPIOx_Sens, uint16_t GPIO_Pin_Sens)
    : Moteur(TIMx, OCx)
{
    this->GPIOx_Sens = GPIOx_Sens;
    this->GPIO_Pin_Sens = GPIO_Pin_Sens;

    // initialiser pins d'entrée sur le STM du port x_sens
    GPIO_InitTypeDef GPIO_InitStructureSortie;
    GPIO_InitStructureSortie.GPIO_Pin =  GPIO_Pin_Sens;
    GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_2MHz;        //La vitesse de rafraichissement du port
    GPIO_Init(GPIOx_Sens, &GPIO_InitStructureSortie);
}

void Roue::tourne(float rapport)
{

    if(rapport >= 0)
    {
        GPIO_WriteBit(GPIOx_Sens, GPIO_Pin_Sens, Bit_RESET);
        pwm.setDutyCycle(rapport);
    }
    else
    {
        GPIO_WriteBit(GPIOx_Sens, GPIO_Pin_Sens, Bit_SET);
        pwm.setDutyCycle(-rapport);
    }

 /*   if(rapport >= 0)
    {
        GPIO_WriteBit(GPIOx_Sens, GPIO_Pin_Sens, Bit_RESET);
    }
    else
    {
        GPIO_WriteBit(GPIOx_Sens, GPIO_Pin_Sens, Bit_SET);
    }

    if(fabs(rapport) < RAPPORT_OK)
        pwm.setDutyCycle(0);
    else
        pwm.setDutyCycle(fabs(rapport)+RAPPORT_SUPPLEMENTAIRE);*/
}
