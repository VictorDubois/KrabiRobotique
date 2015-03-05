#include "pwmHandler.h"

// Initialise un nouveau générateur de PWM sur la sortie OCx du timer TIMx.
PWMHandler::PWMHandler(Timer* tim, unsigned char OCx)
{
    timer = tim;
    this->OCx = OCx;
    TIM_OCInitTypeDef timOCInit;
    timOCInit.TIM_OCMode = TIM_OCMode_PWM1; //TIM_OCMode_PWM2;
    timOCInit.TIM_OutputState = TIM_OutputState_Enable;
    timOCInit.TIM_Pulse = 0; // rapport cyclique
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

// Stoppe la génération de PWM et détruit le générateur de PWM
PWMHandler::~PWMHandler()
{
    setPulseWidth(0);
}

//Change le rapport cyclique
void PWMHandler::setDutyCycle(float dutyCycle)
{
    setPulseWidth(dutyCycle*timer->getPeriod());
}

// Change la taille de l’impulsion.
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
/// @brief initialise une pin pour les pwm
/// Ne pas oublier d'ajouter un eventuel remap pour que la
/// pin corresponde au channel d'un timer
/*void PWMHandler::initialiserPinPourPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x)
{
    GPIO_InitTypeDef GPIO_InitStructureSortie;
    GPIO_InitStructureSortie.GPIO_Pin = GPIO_Pin_x;
    GPIO_InitStructureSortie.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructureSortie.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructureSortie);
}
*/
