
#ifdef STM32F40_41xxx
    #include "stm32f4xx_gpio.h"
    #include "stm32f4xx.h"
    #include "stm32f4xx_rcc.h"

#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x.h"
    #include "stm32f10x_rcc.h"
    #include "stm32f10x_gpio.h"
#endif

#include "quadratureCoderHandler.h"
#include "timerHandler.h"

// GPIO_ch1 et pin_Ch1 : pour la pin du channel 1 du timer
// GPIO_ch2 et pin_Ch2 : pour la pin du channel 2 du timer
QuadratureCoderHandler::QuadratureCoderHandler(TIM_TypeDef* TIMx, GPIO_TypeDef* GPIO_ch1, uint16_t pin_Ch1, GPIO_TypeDef* GPIO_ch2,
                                               uint16_t pin_Ch2, uint8_t TIMx_AF, uint8_t pinSource_Ch1, uint8_t pinSource_Ch2)
{
    this->coder_tim_port = TIMx;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable timer clock
    Timer::enableTimerClock(TIMx);

    // GPIO_Mode_IPD : in pull down
    // GPIO_Mode_IPU : in pull up -> utiliser celui la pour les roue codeuses

    #ifdef STM32F40_41xxx
        // alternative functions
        GPIO_PinAFConfig(GPIO_ch1, pinSource_Ch1, TIMx_AF);
        GPIO_PinAFConfig(GPIO_ch2, pinSource_Ch2, TIMx_AF);
    #endif

    // initialise la pin du ch 1
    #ifdef STM32F40_41xxx
        GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_25MHz;
    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_10MHz;
    #endif

    GPIO_InitStructure.GPIO_Pin     = pin_Ch1;
    GPIO_Init(GPIO_ch1, &GPIO_InitStructure);

    // initialise la pin du ch 2
    #ifdef STM32F40_41xxx
        GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_25MHz;
    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_10MHz;
    #endif
    GPIO_InitStructure.GPIO_Pin     = pin_Ch2;
    GPIO_Init(GPIO_ch2, &GPIO_InitStructure);

    // Time Base configuration
    TIM_TimeBaseStructure.TIM_Prescaler     = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period        = 0xFFFF;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(coder_tim_port, &TIM_TimeBaseStructure);

    // Encoder Interface Configuration
    TIM_EncoderInterfaceConfig(coder_tim_port,
                               TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising,
                               TIM_ICPolarity_Rising);

    // Met à disposition le timer
    TIM_Cmd(coder_tim_port, ENABLE);
}

int16_t QuadratureCoderHandler::getTickValue()
{
    // On enregistre le nbr de tick depuis la dernière remise à zero
    int16_t tick = TIM_GetCounter(coder_tim_port);

    // On remet à zero
    TIM_SetCounter(coder_tim_port, 0);

    // On retourne ces ticks
    return tick;
}
