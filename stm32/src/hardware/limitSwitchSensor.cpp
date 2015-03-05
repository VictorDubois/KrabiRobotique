#include "limitSwitchSensor.h"

#ifdef ROBOTHW
LimitSwitchSensor::LimitSwitchSensor(LimitSwitchSensor::LimitSwitchName name, uint16_t pin, GPIO_TypeDef* group)
{
    this->name = name;
    this->pin = pin;
    this->group = group;
    counter = 0x0;
    output = false;

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin =  pin;
    #ifdef STM32F40_41xxx
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    #endif
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(group, &GPIO_InitStructure);
}

LimitSwitchSensor::~LimitSwitchSensor()
{
}

void  LimitSwitchSensor::updateValue()
{
    counter <<= 1;
    counter |= (GPIO_ReadInputDataBit(group,pin)== Bit_SET);

    // Permet de s'assurer qu'au moins 8 détections succéssive ont eu lieu avant de retourner un true
    // et que rien a été detecté au moins 8 fois pour retourner false.
    output = (counter == 0xff);/*output ? !((counter & 0xff) == 0x00) :*/
}

Sensor::OutputSensor LimitSwitchSensor::getValue()
{
    OutputSensor outputR;
    outputR.type = LIMIT_SWITCH;
    outputR.f = 0;
    outputR.b = this->output;
    return outputR;
}

LimitSwitchSensor::LimitSwitchName LimitSwitchSensor::getName()
{
    return name;
}

#endif
