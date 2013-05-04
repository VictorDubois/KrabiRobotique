#include "roue.h"

#include "stm32f10x_rcc.h"
#include <math.h>

Roue::Roue(TIM_TypeDef* TIMx, unsigned char OCx, GPIO_TypeDef* GPIOx_pwm, uint16_t GPIO_Pin_pwm, GPIO_TypeDef* GPIOx_Sens, uint16_t GPIO_Pin_Sens)
    : Moteur(TIMx, OCx, GPIOx_pwm, GPIO_Pin_pwm)
{
    this->GPIOx_Sens = GPIOx_Sens;
    this->GPIO_Pin_Sens = GPIO_Pin_Sens;

    // GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);

    // initialiser pins d'entrée sur le STM
 //   GPIO_InitTypeDef GPIO_InitStructureSortie;

    // tim 4 ch 4 (ext 1 21)
 //  GPIO_InitStructureSortie.GPIO_Pin = GPIO_Pin_9;
 //   GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_AF_PP;
 //   GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_50MHz;
 //   GPIO_Init(GPIOB, &GPIO_InitStructureSortie);

    // tim 4 ch 2 (ext 1 19)
 //   GPIO_InitStructureSortie.GPIO_Pin = GPIO_Pin_7;
 //   GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_AF_PP;
 //   GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_50MHz;
 //   GPIO_Init(GPIOB, &GPIO_InitStructureSortie);

/*
    // tim 4 ch 2 (ext 1 33)
    GPIO_InitStructureSortie.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructureSortie);

   // tim 4 ch 2 (ext 1 19)
    GPIO_InitStructureSortie.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructureSortie);

    // tim 4 ch 3 (ext 1 34)
    GPIO_InitStructureSortie.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructureSortie);

    // tim 4 ch 4 (ext 1 21)
    GPIO_InitStructureSortie.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructureSortie);

    // tim 4 ch 4 (ext 1 35)
    GPIO_InitStructureSortie.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructureSortie);
*/
    // initialiser pins d'entrée sur le STM du port x_sens
    GPIO_InitTypeDef GPIO_InitStructureSortie2;
    GPIO_InitStructureSortie2.GPIO_Pin =  GPIO_Pin_Sens;
    GPIO_InitStructureSortie2.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructureSortie2.GPIO_Speed = GPIO_Speed_2MHz;        //La vitesse de rafraichissement du port
    GPIO_Init(GPIOx_Sens, &GPIO_InitStructureSortie2);

}

void Roue::tourne(float rapport)
{
    //rapport = 1;
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
  //  pwm.setDutyCycle(rapport); //0.11
/*
    if(fabs(rapport) < RAPPORT_OK)
        pwm.setDutyCycle(0);
    else
        pwm.setDutyCycle(fabs(rapport)+RAPPORT_SUPPLEMENTAIRE);*/
}
