#include "quadrature_coder_handler.h"
//#include "misc.h"
//#include "stdlib.h"

QuadratureCoderHandler::QuadratureCoderHandler(TIM_TypeDef * coder_tim_port){
    //lowerTickValue = 0;
    this->coder_tim_port = coder_tim_port;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    //TIM_ICInitTypeDef       TIM_ICInitStructure;
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
    }

    //Setup timer for quadrature encoder interface
    //Encoder A channel at PA0.0 (Ch1)
    //        B channel at PA0.1 (Ch2)
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_0|GPIO_Pin_1;
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

    //Initialize input capture structure: Ch1
    /*TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel     = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter    = 0;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);*/

    //Initialize input capture structure: Ch2
    /*TIM_ICInitStructure.TIM_Channel     = TIM_Channel_2;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);*/

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

    //Enable coder_tim_port Peripheral
    TIM_Cmd(coder_tim_port, ENABLE);

}

int16_t QuadratureCoderHandler::getTickValue(){
    //uint32_t caca = TIM_GetCounter(coder_tim_port);
    int16_t caca = TIM_GetCounter(coder_tim_port);
    TIM_SetCounter(coder_tim_port, 0);
    return caca;
}
