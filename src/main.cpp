#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include <stdint.h>
#include "misc.h"
#include "servo.h"
#include "rateau.h"
#include "Hctl_Handler.h"
#include "quadrature_coder_handler.h"
#include "asservissement.h"
#include "Position.h"
#include "Angle.h"
#include "PositionPlusAngle.h"
#include "memory.h"
#include "Rouleau.h"
#include "roues.h"
#include "Moteur.h"
#include "capteurs.h"
#include "strategie.h"
#include "odometrie.h"

#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))
//Declarations
void NMI_Handler(void);
void HardFault_Handler(void);
int main(void);

// VARIABLES

GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef TIM2_IRQ;

void Clk_Init();
void myDelay(unsigned long);


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
    /*TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel     = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter    = 0;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);*/

    //Initialize input capture structure: Ch2
   /* TIM_ICInitStructure.TIM_Channel     = TIM_Channel_2;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);*/

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

bool DELenabled = true;

//extern "C" void TIM2_IRQHandler()
//{
    //if( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
//    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    //int a = TIM_GetCounter(TIM2);
    /*if( !DELenabled)
        GPIOC->BRR |= 0x00001000;
    else
        GPIOC->BSRR |= 0x00001000;
    DELenabled = !DELenabled;*/
//}

extern "C" void WWDG_IRQHandler()
{

}

void test_call(int a)
{

}

void fou() {}

/*Mettez toutes vos initialisations de PIN dans la fonction "initialisation"
On l'appellera ensuite dans le main au tout début pour tout initialiser d'un coup
*/
void initialisation()
{
    //Patte coté de la partie bleu ou jaune
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


    //Tirette
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //Pattes des servos
    GPIO_WriteBit(GPIOA,GPIO_Pin_6,Bit_SET);
    //GPIO_Write(GPIOB, 0xffff);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_RESET);
    //GPIO_Write(GPIOB, 0xffff);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

}

bool isBlue()
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)  == Bit_SET;
}

bool isTiretteEnleve()
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)  == Bit_SET;
}

/*************************************************************************
 * Function Name: main
 * Parameters: none
 * Return: Int32U
 *
 * Description: The main subroutine
 *
 *************************************************************************/
int main(void)
{

	*NVIC_CCR = *NVIC_CCR | 0x200; /* Set STKALIGN in NVIC */
	// Init clock system
	  Clk_Init();


    RCC_PCLK2Config(RCC_HCLK_Div8); // nécessaire pour le bon fonctionnement de l'ADC
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);


//Appel de la fonction qui permet d'initialiser tous les PINS
initialisation();


/*
    unsigned int buffer = 0xffffffff;

    while(buffer)
    {
        buffer <<= 1;
        bool tmp = !isTiretteEnleve();
        buffer |= tmp;
    }
*/
    Strategie strategie(isBlue(), new Asservissement(new HwOdometrie(new QuadratureCoderHandler(TIM2), new QuadratureCoderHandler(TIM1))));
    while(1);
}
void NMI_Handler(void)
{
	return ;
}

void HardFault_Handler(void)
{
	return ;
}
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

void Clk_Init (void)
{
  // 1. Cloking the controller from internal HSI RC (8 MHz)
  RCC_HSICmd(ENABLE);
  // wait until the HSI is ready
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
  // 2. Enable ext. high frequency OSC
  RCC_HSEConfig(RCC_HSE_ON);
  // wait until the HSE is ready
  while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
  // 3. Init PLL
  RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9); // 72MHz
//  RCC_PLLConfig(RCC_PLLSource_HSE_Div2,RCC_PLLMul_9); // 72MHz
  RCC_PLLCmd(ENABLE);
  // wait until the PLL is ready
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  // 4. Set system clock divders
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
  RCC_ADCCLKConfig(RCC_PCLK2_Div8);
  RCC_PCLK2Config(RCC_HCLK_Div1);
  RCC_PCLK1Config(RCC_HCLK_Div2);
  RCC_HCLKConfig(RCC_SYSCLK_Div1);
  // Flash 1 wait state
  *(vu32 *)0x40022000 = 0x12;
  // 5. Clock system from PLL
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}
