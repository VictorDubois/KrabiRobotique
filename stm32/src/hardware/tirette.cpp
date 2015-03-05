#include "tirette.h"

#include "remote.h"
#include "leds.h"


// initialise la pin de la tirette
Tirette::Tirette(GPIO_TypeDef* GPIOx_tirette, uint16_t GPIO_Pin_x_tirette)
    : GPIOx(GPIOx_tirette), GPIO_Pin_x(GPIO_Pin_x_tirette)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x_tirette;

    #ifdef STM32F40_41xxx
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    #endif

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx_tirette, &GPIO_InitStructure);
}

// attends jusqu'à ce que la tirette soit enlevée
void Tirette::attendreEnlevee() const
{
    Remote::log("Waiting for 'tirette enleve'");

    int buffer = 0xffffffff;
    //int waiting = 0;
    while (buffer)
    {
        Remote::getSingleton()->update(true);
        if (Remote::getSingleton()->isRemoteMode())
            break;

        buffer <<= 1;
        buffer |= !enlevee();
    }
}

// attends jusqu'à ce que la tirette soit remise
void Tirette::attendreRemise() const
{
    Remote::log("Waiting for 'tirette remise'");

    int buffer = 0xffffffff;
    while (buffer)
    {
        Remote::getSingleton()->update(true);
        if (Remote::getSingleton()->isRemoteMode())
            break;

        buffer <<= 1;
        buffer |= enlevee();
    }
}

// est ce que la tirette est enlevée ?
bool Tirette::enlevee() const
{
    #ifdef STM32F40_41xxx
        return GPIO_ReadInputDataBit(GPIOx, GPIO_Pin_x) == Bit_RESET;
    #else
        return GPIO_ReadInputDataBit(GPIOx, GPIO_Pin_x) == Bit_SET;
    #endif
}
