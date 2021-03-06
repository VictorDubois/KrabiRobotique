#include "ultrasoundSensor.h"

float UltrasoundSensor::coeff = COEFFICIENT_LIN_ULTRASON;

UltrasoundSensor::UltrasoundSensor(UltrasoundName name, uint8_t channel, DMA_MEMORY_TYPE* pData) : AnalogSensor(channel, pData)
{
    this->name = name;
}

UltrasoundSensor::~UltrasoundSensor()
{
    //dtor
}

UltrasoundSensor::UltrasoundName UltrasoundSensor::getName()
{
    return name;
}


Sensor::OutputSensor UltrasoundSensor::getValue()
{
    while(!AnalogSensor::conversionFinished());    // au cas où l'interrupt de l'asservissement tombe avant la fin de l'acquisition/conversion
    /***********************************************
     **                                           **
     **                                           **
     ** C'EST ICI QU'IL FAUT METTRE LE BREAKPOINT **
     **     POUR AVOIR LA VALEUR DES CAPTEURS     **
     **                                           **
     **                                           **
     ***********************************************/
    OutputSensor output;
    output.type = ULTRASOUND;
    output.b = false;
    #ifdef ROBOTHW
    output.f = coeff*(*data)/2.;
    #else
    output.f = 0;
    #endif
    return output;
}


