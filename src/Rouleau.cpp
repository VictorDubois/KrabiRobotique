#include "Rouleau.h"

Rouleau::Rouleau(float dutyCycle) : Moteur(1){
    // propager horloge aux ports A et B
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // initialiser pins de sortie sur le STM du port A
    GPIO_InitTypeDef GPIO_InitStructureSortie;
    GPIO_InitStructureSortie.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_Out_PP;         // Le mode sortie Out_OD
    GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_2MHz;        //La vitesse de rafraichissement du port
    GPIO_Init(GPIOA, &GPIO_InitStructureSortie);


    // initialiser pins d'entrÃ©e sur le STM du port B
    GPIO_InitTypeDef GPIO_InitStructureSortie2;
    GPIO_InitStructureSortie2.GPIO_Pin =  GPIO_Pin_6;
    GPIO_InitStructureSortie2.GPIO_Mode = GPIO_Mode_AF_PP;        // Le mode sortie Out_OD
    GPIO_InitStructureSortie2.GPIO_Speed = GPIO_Speed_2MHz;        //La vitesse de rafraichissement du port
    GPIO_Init(GPIOB, &GPIO_InitStructureSortie2);

    // initialiser pins d'entrÃ©e sur le STM du port B
    GPIO_InitTypeDef GPIO_InitStructureSortie3;
    GPIO_InitStructureSortie3.GPIO_Pin =  GPIO_Pin_7;
    GPIO_InitStructureSortie3.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructureSortie3.GPIO_Speed = GPIO_Speed_2MHz;        //La vitesse de rafraichissement du port
    GPIO_Init(GPIOB, &GPIO_InitStructureSortie3);

    this->dutyCycle = dutyCycle;

    /*const Timer::ClkDivision timClockDivision = Timer::Div1;

    pwm(new Timer(0, 0, 0, timClockDivision), OCx);*/
    //initialisation de l'angle
}


void Rouleau::avaleBoule(){
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET);
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
    tourne(dutyCycle);
}

void Rouleau::recracheBoule(){
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET);
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
    tourne(dutyCycle);
}

void Rouleau::arrete(){
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET);
}
