#include "ligthBarrierSensor.h"

#ifdef ROBOTHW

LigthBarrierSensor::LigthBarrierSensor(LigthBarrierName name, uint16_t pin, GPIO_TypeDef* group)
{
    this->pin = pin;
    this->group = group;
    counter = 0;
    this->name = name;
    output = false;

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin =  pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(group, &GPIO_InitStructure);
}

LigthBarrierSensor::~LigthBarrierSensor()
{
}

void LigthBarrierSensor::updateValue()
{
    counter <<=1;
    counter |= (GPIO_ReadInputDataBit(group,pin)==SET);

    // Permet de s'assurer qu'au moins 8 détections succéssive ont eu lieu avant de
    // retourner un true et que rien a été detecté au moins 8 fois pour retourner false.
    output = output ? !((counter & 0xff) == 0x00) : (counter & 0xff) == 0xff ;
}

Sensor::OutputSensor LigthBarrierSensor::getValue()
{
    OutputSensor outputR;
    outputR.type = LIMIT_SWITCH;
    outputR.f = 0;
    outputR.b = output;
    return outputR;
}

LigthBarrierSensor::LigthBarrierName LigthBarrierSensor::getName()
{
    return name;
}

#endif

