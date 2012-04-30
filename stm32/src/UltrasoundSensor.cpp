#include "UltrasoundSensor.h"

#ifdef ROBOTHW


float UltrasoundSensor::coeff = COEFFICIENT_LIN_ULTRASON;

UltrasoundSensor::UltrasoundSensor(UltrasoundName name, uint8_t channel, uint16_t* pData) : AnalogSensor(channel, pData)
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
    output.f = coeff*(*data)/2.;
    return output;
}

#endif
