#include "quadrature_coder_handler.h"

//Objet permettant de savoir le nombre de tick fait par la roux codeuse
QuadratureCoderHandler::QuadratureCoderHandler(TIM_TypeDef * coder_tim_port){
    //lowerTickValue = 0;
    this->coder_tim_port = coder_tim_port;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef       TIM_ICInitStructure;
    GPIO_InitTypeDef        GPIO_InitStructure;

    //Enable GPIOA clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //Enable timer clock
    if(coder_tim_port == TIM1){
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    } else if(coder_tim_port == TIM2){
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    } else if(coder_tim_port == TIM3){
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    } else if(coder_tim_port == TIM4){
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    } else if(coder_tim_port == TIM5){
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    } else if(coder_tim_port == TIM6){
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    } else if(coder_tim_port == TIM7){
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    }

    //Setup timer for quadrature encoder interface
    //Encoder A channel at PA0.0 (Ch1)
    //        B channel at PA0.1 (Ch2)
#ifdef STM32F10X_MD
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_0|GPIO_Pin_1;
#endif
#ifdef STM32F10X_CL
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
#endif
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //Time Base configuration
    TIM_TimeBaseStructure.TIM_Prescaler     = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period        = 0xFFFF;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(coder_tim_port, &TIM_TimeBaseStructure);

    //On constate que, sur le STM32_h107, la roue coudeuse droite est branché sur les pin PA0 et PA1 qui posséde les TIM2 et TIM5 avec comme channel 1 et 2
    // et la roue coudeuse gauche sur PA2 et PA3 qui posséde aussi les TIM2 et TIM3 mais sur le channel 3 et 4.
    // On choisit le TIM2 pour la roue droite et TIM5 pour la gauche

#ifdef STM32F10X_CL

    if(coder_tim_port == TIM5)
    {

        //Initialize input capture structure: Ch3
        TIM_ICStructInit(&TIM_ICInitStructure);
        TIM_ICInitStructure.TIM_Channel     = TIM_Channel_3;
        TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
        TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
        TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
        TIM_ICInitStructure.TIM_ICFilter    = 0;
        TIM_ICInit(TIM5, &TIM_ICInitStructure);

        //Initialize input capture structure: Ch4
        TIM_ICInitStructure.TIM_Channel     = TIM_Channel_4;
        TIM_ICInit(TIM5, &TIM_ICInitStructure);
    }
#endif

    //Encoder Interface Configuration
    TIM_EncoderInterfaceConfig(coder_tim_port,
                               TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising,
                               TIM_ICPolarity_Rising);
    /*NVIC_InitTypeDef TIMx_IRQ;
    if(coder_tim_port == TIM1){
        QuadratureCoderHandler::TIM1_QuadratureCoderHandler = this;
        TIMx_IRQ.NVIC_IRQChannel = TIM1_CC_IRQn;
    } else if(coder_tim_port == TIM2){
        QuadratureCoderHandler::TIM2_QuadratureCoderHandler = this;
        TIMx_IRQ.NVIC_IRQChannel = TIM2_IRQn;
    } else if(coder_tim_port == TIM3){
        QuadratureCoderHandler::TIM3_QuadratureCoderHandler = this;
        TIMx_IRQ.NVIC_IRQChannel = TIM3_IRQn;
    } else if(coder_tim_port == TIM4){
        QuadratureCoderHandler::TIM4_QuadratureCoderHandler = this;
        TIMx_IRQ.NVIC_IRQChannel = TIM4_IRQn;
    }
    TIMx_IRQ.NVIC_IRQChannelCmd = ENABLE;
    TIMx_IRQ.NVIC_IRQChannelPreemptionPriority = 0;
    TIMx_IRQ.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&TIMx_IRQ);*/

    //TIM_ITConfig(coder_tim_port, TIM_IT_Update, ENABLE);

    //Met à disposition le timer
    TIM_Cmd(coder_tim_port, ENABLE);

}

int16_t QuadratureCoderHandler::getTickValue(){

    int16_t tick = TIM_GetCounter(coder_tim_port);    //On enregistre le nbr de tick depuis la derniére remise à zero
    TIM_SetCounter(coder_tim_port, 0);                          //On remet à zero
    return tick;                                      //On retourne ces ticks
}
