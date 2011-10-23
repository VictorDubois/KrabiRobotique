#include "roue.h"

Roue::Roue(unsigned char OCx, GPIO_TypeDef * GPIOx_Sens, uint16_t GPIO_Pin_Sens) : Moteur(OCx){
    this->GPIOx_Sens = GPIOx_Sens;
    this->GPIO_Pin_Sens = GPIO_Pin_Sens;

	//On propage l'horloge
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // initialiser pins d'entrÃ©e sur le STM du port B
    GPIO_InitTypeDef GPIO_InitStructureSortie;
    GPIO_InitStructureSortie.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_6 | GPIO_Pin_9; // Malheureusement c'est trop relou de trouver que c'est PB8 et PB9 a partir de TIM4_(OCx) alors on met direct les bonnes valeurs !
    GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_AF_PP;        // Le mode sortie Out_OD
    GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_2MHz;        //La vitesse de rafraichissement du port
    GPIO_Init(GPIOB, &GPIO_InitStructureSortie);

    // initialiser pins d'entrÃ©e sur le STM du port x_sens
    GPIO_InitTypeDef GPIO_InitStructureSortie2;
    GPIO_InitStructureSortie2.GPIO_Pin =  GPIO_Pin_Sens;
    GPIO_InitStructureSortie2.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructureSortie2.GPIO_Speed = GPIO_Speed_2MHz;        //La vitesse de rafraichissement du port
    GPIO_Init(GPIOx_Sens, &GPIO_InitStructureSortie2);

}


void Roue::tourne(float rapport)
{
    //rapport = -0.3;
    if(rapport >= 0){
        GPIO_WriteBit(GPIOx_Sens, GPIO_Pin_Sens, Bit_RESET);
    }
    else {
        GPIO_WriteBit(GPIOx_Sens, GPIO_Pin_Sens, Bit_SET);
    }

    if(fabs(rapport) < RAPPORT_OK)
        pwm.setDutyCycle(0);
    else
        pwm.setDutyCycle(fabs(rapport)+RAPPORT_SUPPLEMENTAIRE);
}
