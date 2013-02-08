#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "quadratureCoderHandler.h"

// Classe permettant de connaitre le nombre de ticks des roues codeuses
QuadratureCoderHandler::QuadratureCoderHandler(TIM_TypeDef* tim)
{
    this->coder_tim_port = tim;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
/*
    // Enable GPIOA clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // Enable GPIOE clock
#ifdef STM32F10X_CL // stm h107
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
#endif
*/

    // Enable timer clock
    if (coder_tim_port == TIM1)
    {
        //RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }
    else if (coder_tim_port == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }
    else if (coder_tim_port == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    }
    else if (coder_tim_port == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    }
    else if (coder_tim_port == TIM5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    }
    else if (coder_tim_port == TIM6)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    }
    else if (coder_tim_port == TIM7)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    }

    //Setup timer for quadrature encoder interface
    //Encoder A channel at PA0.0 (Ch1)
    //        B channel at PA0.1 (Ch2)
/*
#ifdef STM32F10X_MD // stm h103
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_0|GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif*/

#ifdef STM32F10X_CL // stm h107
// GPIO_Mode_IPD : in pull down
// GPIO_Mode_IPU : in pull up
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IPU;//GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_9|GPIO_Pin_11;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_0|GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_2|GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_12|GPIO_Pin_13;
    GPIO_Init(GPIOD, &GPIO_InitStructure);



#endif

    // Time Base configuration
    TIM_TimeBaseStructure.TIM_Prescaler     = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period        = 0xFFFF;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(coder_tim_port, &TIM_TimeBaseStructure);

    // Encoder Interface Configuration
    TIM_EncoderInterfaceConfig(coder_tim_port,
                               TIM_EncoderMode_TI12,//TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising,
                               TIM_ICPolarity_Rising);

    // Met à disposition le timer
    TIM_Cmd(coder_tim_port, ENABLE);



}

int16_t QuadratureCoderHandler::getTickValue(){

    int16_t tick = TIM_GetCounter(coder_tim_port); // On enregistre le nbr de tick depuis la derniére remise à zero
    TIM_SetCounter(coder_tim_port, 0);             // On remet à zero
    return tick;                                   // On retourne ces ticks
}
