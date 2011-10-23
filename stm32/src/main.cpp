#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include <stdint.h>
#include "misc.h"
#include "servo.h"
#include "Hctl_Handler.h"
#include "quadrature_coder_handler.h"
#include "asservissement.h"
#include "Position.h"
#include "Angle.h"
#include "PositionPlusAngle.h"
#include "memory.h"
#include "roues.h"
#include "Moteur.h"
#include "capteurs.h"
#include "strategie.h"
#include "odometrie.h"
#include "stm32f10x.h"

#ifdef POSITIONNEMENT
#include "command.h"
#endif

#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))
//Declarations
void Clk_Init();
void myDelay(unsigned long);
void initTimer();
int main();

// VARIABLES

GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef TIM2_IRQ;

void initTimer()
{
    /*
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    TIM_TimeBaseInitTypeDef timInit;
    timInit.TIM_Prescaler = 36000;
    timInit.TIM_CounterMode = TIM_CounterMode_Up;
    timInit.TIM_Period = 2000;
    timInit.TIM_ClockDivision = TIM_CKD_DIV2;
    timInit.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timInit);

    TIM2_IRQ.NVIC_IRQChannel = TIM2_IRQn;
    TIM2_IRQ.NVIC_IRQChannelCmd = ENABLE;
    TIM2_IRQ.NVIC_IRQChannelPreemptionPriority = 0;
    TIM2_IRQ.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&TIM2_IRQ);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);*/

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    TIM_TimeBaseInitTypeDef timInit;
    timInit.TIM_Prescaler = 0;
    timInit.TIM_CounterMode = TIM_CounterMode_Up;
    timInit.TIM_Period = 3000;
    timInit.TIM_ClockDivision = 0;
    timInit.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timInit);

    TIM_OCInitTypeDef timOCInit;
    timOCInit.TIM_OCMode =TIM_OCMode_PWM1;
    timOCInit.TIM_OutputState = TIM_OutputState_Enable;
    timOCInit.TIM_Pulse = 800; /* rapport cyclique */
    timOCInit.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC3Init(TIM2, &timOCInit);

    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM2, ENABLE);


    TIM_Cmd(TIM2, ENABLE);
}

/* fonction inutilisé ...
void initQuadEncoderCounter(){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    //TIM_ICInitTypeDef       TIM_ICInitStructure;
    GPIO_InitTypeDef        GPIO_InitStructure;

    //Enable GPIOA clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //Enable timer clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    //Setup timer for quadrature encoder interface
    //Encoder A channel at PA0.0 (Ch1)
    //        B channel at PA0.1 (Ch2)
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //Time Base configuration
    TIM_TimeBaseStructure.TIM_Prescaler     = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period        = 0xFFFF;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    //Initialize input capture structure: Ch1
    *//*TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel     = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter    = 0;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);*/

    //Initialize input capture structure: Ch2
   /* TIM_ICInitStructure.TIM_Channel     = TIM_Channel_2;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);*//*

    //Encoder Interface Configuration
    TIM_EncoderInterfaceConfig(TIM2,
                               TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising,
                               TIM_ICPolarity_Rising);

    TIM2_IRQ.NVIC_IRQChannel = TIM2_IRQn;
    TIM2_IRQ.NVIC_IRQChannelCmd = ENABLE;
    TIM2_IRQ.NVIC_IRQChannelPreemptionPriority = 0;
    TIM2_IRQ.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&TIM2_IRQ);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    //Enable TIM2 Peripheral
    TIM_Cmd(TIM2,ENABLE);
}
*/
/*
bool DELenabled = true;

extern "C" void TIM2_IRQHandler()
{
    if( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    int a = TIM_GetCounter(TIM2);
    if( !DELenabled)
        GPIOC->BRR |= 0x00001000;
    else
        GPIOC->BSRR |= 0x00001000;
    DELenabled = !DELenabled;
}*/
/* inutilisé et vide ...
extern "C" void WWDG_IRQHandler()
{

}
*/
/*Mettez toutes vos initialisations de PIN dans la fonction "initialisation"
On l'appellera ensuite dans le main au tout début pour tout initialiser d'un coup
*/
void initialisation()
{
    //Patte coté de la partie bleu ou jaune
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


    //Tirette
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


// GPIO_InitTypeDef GPIO_InitStructureTest;   //Alim Fdc Haut
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;        //La vitesse de rafraichissement du port
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET);

        //Fin de Course Haut ?
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

        //Fin de course bas ?
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

        //Fin de course pion ?
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //Pattes des servos
//    GPIO_WriteBit(GPIOA,GPIO_Pin_6,Bit_SET);  //servo droite
//    GPIO_Write(GPIOB, 0xffff);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_RESET);   // servo gauche
//    GPIO_Write(GPIOB, 0xffff);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

  // GPIO_InitTypeDef GPIO_InitStructureTest;   //LED
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;        //La vitesse de rafraichissement du port
   GPIO_Init(GPIOC, &GPIO_InitStructure);
   GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);

/*
 // GPIO_InitTypeDef GPIO_InitStructureTest;   //TEST
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;        //La vitesse de rafraichissement du port
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_SET);
*/
}

/* Inutil puisqu'elle n'est pas utilisé
//Pour s'orienter si on est (ou pas) du coté bleu
#ifdef POSITIONNEMENT
void positionnement(bool is_blue)
{
    this->is_blue = is_blue;
    int cote = (is_blue ? 1:-1);
}
#endif
*/

//Dis si on est du coté bleu
bool isBlue()
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)  == Bit_RESET;
}

//Dis si la tirette est enleve
bool isTiretteEnleve()
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)  == Bit_SET;
}

/* fonction inutilisé
// Fonction pour tester les capteurs en allument la led verte du stm
void test_capteurs_sharp ()
{
#ifndef INITLED
#define INITLED
       // initialiser pins d'entrée sur le STM
   GPIO_InitTypeDef GPIO_InitStructureTest;
   GPIO_InitStructureTest.GPIO_Pin =  GPIO_Pin_12;
   GPIO_InitStructureTest.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructureTest.GPIO_Speed = GPIO_Speed_2MHz;        //La vitesse de rafraichissement du port
   GPIO_Init(GPIOC, &GPIO_InitStructureTest);
#endif

    Capteurs capteurs;
//Capteurs.capteurs();

    while(true)
    {
    capteurs.startConversion();
    bool testcap = capteurs.getValue(Capteurs::AvantDroitExt) || capteurs.getValue(Capteurs::AvantDroitInt) || capteurs.getValue(Capteurs::AvantGaucheExt) || capteurs.getValue(Capteurs::AvantGaucheInt) || capteurs.getValue(Capteurs::Derriere) ;
    if (testcap)
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
    }
    else
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
    }
    }
}
*/

/*************************************************************************
 * Function Name: main
 * Parameters: none
 * Return: Int32U
 *
 * Description: The main subroutine
 *
 *************************************************************************/

int main()
{
	*NVIC_CCR = *NVIC_CCR | 0x200; /* Set STKALIGN in NVIC */

    //On initialise les horloges
    Clk_Init();

    //On définit quelques horloges supplémentaires
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

    //Appel de la fonction qui permet d'initialiser tous les PINS
    initialisation();

//fonction de test des fin de course
/*
while(1)
{
    if ((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10)  == Bit_RESET)||(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9)  == Bit_RESET))                   // TEST DES FDC seule la pin 9 fonctionne (on a branché le fdc bas sur cette pin)
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
    }
    else
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
    }
}
*/

    unsigned int buffer = 0xffffffff;

    //On boucle tant que la tirette est pas enlever avec 32 verification au cas ou il y ai du bruit
    while(buffer)
    {
        buffer <<= 1;
        buffer |= !isTiretteEnleve();
    }

//Une fois que la tirette est enlevée pour la 1ère fois, on lance le positionnement automatique
    Odometrie* odometrie = new Odometrie(new QuadratureCoderHandler(TIM1), new QuadratureCoderHandler(TIM2));
    new Asservissement(odometrie);  // On définie l'asservissement
    Servo::initTimer();     // A faire avant tout utilisation de servo

#ifdef POSITIONNEMENT
// --- Fonction de positionnement, on charge l'odometrie et l'asservissement puis on se remet comme au début du match--- //
//positionnement();    // Fonction inexistante???????

    unsigned int buffer = 0xffffffff;
//on attend que la tirette soit remise
    while(buffer)
    {
        buffer <<= 1;
        buffer |= isTiretteEnleve();
    }

       unsigned int buffer = 0xffffffff;
//on attend que la tirette soit enlevée pour le début du match
    while(buffer)
    {
        buffer <<= 1;
        bool tmp = isTiretteEnleve();
        buffer |= tmp;
    }

#endif



    Strategie strategie(isBlue(),odometrie);
//  test_capteurs_sharp ();
    while(1);
}

/*uint32_t val = 0 ;

extern "C" void UsageFault_Handler(void)
{
    val = SCB->CFSR;
    for(;;);
	return ;
}

extern "C" void USB_LP_CAN1_RX0_IRQHandler (void)
{
    for (;;);
}*/

//Functions definitions
void myDelay(unsigned long delay )
{
  while(delay) delay--;
}

/*************************************************************************
 * Function Name: Clk_Init
 * Parameters: Int32U Frequency
 * Return: Int32U
 *
 * Description: Init clock system
 *
 *************************************************************************/

void Clk_Init()
{
  // Demare l'horloge interne (8 MHz)
  RCC_HSICmd(ENABLE);
  // On attend qu'elle soit allume
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  // Une fois demare, on utilise celle ci
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
  // Demare l'horloge externe
  RCC_HSEConfig(RCC_HSE_ON);
  // On attend qu'elle soit allume
  while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
  // Initialisation du PLL sur l'horloge HSE et multiplication de la frequence par 9
  RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9); // 72MHz
  // On demarre le PLL une fois la config entre
  RCC_PLLCmd(ENABLE);
  // On attend qu'il soit vraiment allume
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  // On demare les composant interne au microcontroleur
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
  RCC_ADCCLKConfig(RCC_PCLK2_Div8);
  RCC_PCLK2Config(RCC_HCLK_Div8);
  RCC_PCLK1Config(RCC_HCLK_Div2);
  RCC_HCLKConfig(RCC_SYSCLK_Div1);
  // Flash 1 wait state
  *(vu32 *)0x40022000 = 0x12;
  // On utilise le PLL comme horloge de reference
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}
