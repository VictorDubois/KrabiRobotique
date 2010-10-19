#include "pwm_handler.h"
#include "timer_handler.h"


PWMHandler::PWMHandler(Timer *tim, unsigned char OCx)
{
    timer = tim;
    this->OCx = OCx;
    TIM_OCInitTypeDef timOCInit;
    timOCInit.TIM_OCMode =TIM_OCMode_PWM1;
    timOCInit.TIM_OutputState = TIM_OutputState_Enable;
    timOCInit.TIM_Pulse = 0; /* rapport cyclique */
    timOCInit.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_TypeDef* TIMx = tim->getTIMx();

    switch(OCx)
    {
        case 1:
        TIM_OC1Init(TIMx, &timOCInit);
        TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
        break;
        case 2:
        TIM_OC2Init(TIMx, &timOCInit);
        TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
        break;
        case 3:
        TIM_OC3Init(TIMx, &timOCInit);
        TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
        break;
        case 4:
        TIM_OC4Init(TIMx, &timOCInit);
        TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
        break;
    }
    TIM_ARRPreloadConfig(TIMx, ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}

void PWMHandler::setPulseWidth(uint16_t pulseWidth)
{
    TIM_TypeDef* TIMx = timer->getTIMx();
    if(OCx == 1)
        TIMx->CCR1 = pulseWidth;
    else if(OCx == 2)
        TIMx->CCR2 = pulseWidth;
    else if(OCx == 3)
        TIMx->CCR3 = pulseWidth;
    else if(OCx == 4)
        TIMx->CCR4 = pulseWidth;
}

void PWMHandler::setDutyCycle(float dutyCycle)
{
    setPulseWidth(dutyCycle*timer->getPeriod());
}

PWMHandler::~PWMHandler()
{
    setPulseWidth(0);
}
