#include "sharpSensor.h"
#include "leds.h"

int SharpSensor::threshold = SEUIL_DETECTION;
bool SharpSensor::estDesactive = false;

SharpSensor::SharpSensor(SharpName name, uint8_t channel, DMA_MEMORY_TYPE* pData, int seuil) : AnalogSensor(channel, pData)
{
    this->name = name;
    counter = 0;
    output = false;
    actif = true;
    seuilDetection = seuil;
    value = 0;
    #ifndef ROBOTHW
    this->evt = false;
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

    #if defined(STM32F10X_MD) || defined(STM32F40_41xxx) // KJ - H405
        value = *data;
        value >>= 4;
    #else // K - H107
        value = *data;
    #endif

    counter <<= 1;
    counter |= (value > seuilDetection);
    //if (*data > threshold)
    //    allumerLED();
    output = output ? !((counter & 0xff) == 0x00) : (counter & 0xff) == 0xff ; // Permet de s'assurer qu'au moins 8 détections succéssive ont eu lieu avant de retourner un true et que rien a été detecté au moins 8 fois pour retourner false.
    #else
    //std::cout << "Capteur Sharp : '" << this->name << "'', actif==" << this->actif << ", evt==" << this->evt << "\n";

    if (evt){
        output = true;
        //evt = false;
        //stop = false;
    }
    else
        output = false;
    #endif

}

Sensor::OutputSensor SharpSensor::getValue()
{
    OutputSensor outputR;
    outputR.type = SHARP;
    outputR.f = (float)value;
    outputR.b = (output && actif);// && actif && !SharpSensor::estDesactive);
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
    this->evt=true;
}

void SharpSensor::unsetEvent()
{
    this->evt=false;
}
#endif


