#include "SharpSensor.h"

uint16_t SharpSensor::threshold = SEUIL_DETECTION;

SharpSensor::SharpSensor(SharpName name, uint8_t channel, uint16_t* pData) : AnalogSensor(channel, pData)
{
    this->name = name;
    counter = 0;
}

SharpSensor::~SharpSensor()
{
    //dtor
}

Sensor::OutputSensor SharpSensor::getValue()
{
    OutputSensor output;
    output.type = SHARP;
    output.f = 0;
    counter <<= 1;
    counter |= (*data < threshold);
    output.b = output.b ? !((counter & 0x0f) == 0x00) : (counter & 0xff) == 0xff ; // Permet de s'assurer qu'au moins 8 détections succéssive ont eu lieu avant de retourner un true et que rien a été detecté au moins 4 fois pour retourner false.
    return output;
}

SharpSensor::SharpName SharpSensor::getName()
{
    return name;
}
