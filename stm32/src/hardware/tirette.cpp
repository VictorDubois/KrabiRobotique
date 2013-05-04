#include "tirette.h"


// initialise la pin de la tirette
Tirette::Tirette(GPIO_TypeDef* GPIOx_tirette, uint16_t GPIO_Pin_x_tirette)
    : GPIOx(GPIOx_tirette), GPIO_Pin_x(GPIO_Pin_x_tirette)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x_tirette;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx_tirette, &GPIO_InitStructure);
}

// attends jusqu'à ce que la tirette soit enlevée
void Tirette::attendreEnlevee() const
{
    int buffer = 0xffffffff;
    while (buffer)
    {
        buffer <<= 1;
        buffer |= !enlevee();
    }
}

// attends jusqu'à ce que la tirette soit remise
void Tirette::attendreRemise() const
{
    int buffer = 0xffffffff;
    while (buffer)
    {
        buffer <<= 1;
        buffer |= enlevee();
    }
}

// est ce que la tirette est enlevée ?
bool Tirette::enlevee() const
{
    return GPIO_ReadInputDataBit(GPIOx, GPIO_Pin_x) == Bit_SET;
}
