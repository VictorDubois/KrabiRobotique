#include "LimitSwitchSensor.h"

LimitSwitchSensor::LimitSwitchSensor(LimitSwitchSensor::LimitSwitchName name, uint16_t pin, GPIO_TypeDef* group)
{
    this->name = name;
    this->pin = pin;
    this->group = group;
    counter = 0;

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin =  pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(group, &GPIO_InitStructure);

}

LimitSwitchSensor::~LimitSwitchSensor()
{
    //dtor
}

Sensor::OutputSensor LimitSwitchSensor::getValue()
{
    OutputSensor output;
    output.type = LIMIT_SWITCH;
    output.f = 0;
    counter <<=1;
    counter |= (GPIO_ReadInputDataBit(group,pin)==SET);
    output.b = output.b ? !((counter & 0x0f) == 0x00) : (counter & 0xff) == 0xff ; // Permet de s'assurer qu'au moins 8 détections succéssive ont eu lieu avant de retourner un true et que rien a été detecté au moins 4 fois pour retourner false.
    return output;
}

LimitSwitchSensor::LimitSwitchName LimitSwitchSensor::getName()
{
    return name;
}
