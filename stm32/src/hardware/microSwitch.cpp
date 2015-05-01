#include "microSwitch.h"

// initialise la pin deu microSwitch
MicroSwitch::MicroSwitch(GPIO_TypeDef* GPIOx_microSwitch, uint16_t GPIO_Pin_x_microSwitch)
    : GPIOx(GPIOx_microSwitch), GPIO_Pin_x(GPIO_Pin_x_microSwitch)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x_microSwitch;

    #ifdef STM32F40_41xxx
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    #endif

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx_microSwitch, &GPIO_InitStructure);
}

// est ce que le microSwitch est fermé ?
bool MicroSwitch::ferme() const
{
    return GPIO_ReadInputDataBit(GPIOx, GPIO_Pin_x) == Bit_RESET;
}

