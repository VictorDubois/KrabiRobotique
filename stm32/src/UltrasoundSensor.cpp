#include "UltrasoundSensor.h"

float UltrasoundSensor::coeff = COEFFICIENT_LIN_ULTRASON;

UltrasoundSensor::UltrasoundSensor(uint8_t channel, uint16_t* pData) : AnalogSensor(channel, pData)
{

}

UltrasoundSensor::~UltrasoundSensor()
{
    //dtor
}


Sensor::OutputSensor UltrasoundSensor::getValue()
{
    OutputSensor output;
    output.type = ULTRASOUND;
    output.b = false;
    output.f = coeff*(*data)/2.;
    return output;
}
