#include "sharpSensor.h"
#include "leds.h"
uint16_t SharpSensor::threshold = SEUIL_DETECTION;
bool SharpSensor::estDesactive = false;

SharpSensor::SharpSensor(SharpName name, uint8_t channel, uint16_t* pData, uint16_t seuil) : AnalogSensor(channel, pData)
{
    this->name = name;
    counter = 0;
    output = false;
    actif = true;
    seuilDetection = seuil;
    #ifndef ROBOTHW
    evt = false;
    #endif

}

SharpSensor::~SharpSensor()
{
    //dtor
}

void SharpSensor::updateValue()
{
    #ifdef ROBOTHW
    while(!AnalogSensor::conversionFinished());    // au cas où l'interrupt de l'asservissement tombe avant la fin de l'acquisition/conversion
    /***********************************************
     **                                           **
     **                                           **
     ** C'EST ICI QU'IL FAUT METTRE LE BREAKPOINT **
     **     POUR AVOIR LA VALEUR DES CAPTEURS     **
     **                                           **
     **                                           **
     ***********************************************/
    counter <<= 1;
    counter |= (*data > seuilDetection);
    //if (*data > threshold)
    //    allumerLED();
    output = output ? !((counter & 0xff) == 0x00) : (counter & 0xff) == 0xff ; // Permet de s'assurer qu'au moins 8 détections succéssive ont eu lieu avant de retourner un true et que rien a été detecté au moins 8 fois pour retourner false.
    #else
    if (evt){
        output = true;
        evt = false;
    }
    else
        output = false;
    #endif

}

Sensor::OutputSensor SharpSensor::getValue()
{
    OutputSensor outputR;
    outputR.type = SHARP;
    outputR.f = 0;
    outputR.b = (output);// && actif && !SharpSensor::estDesactive);
    return outputR;
}

SharpSensor::SharpName SharpSensor::getName()
{
    return name;
}


void SharpSensor::setActif()
{
    actif = true;
}

void SharpSensor::unsetActif()
{
    actif = false;
}


#ifndef ROBOTHW
void SharpSensor::setEvent()
{
    evt=true;
}
#endif


