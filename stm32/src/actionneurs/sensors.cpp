#include "sensors.h"

Sensors* Sensors::sensors = NULL;

Sensors::Sensors()
{
    Sensors::sensors = this;

    //uint8_t channels[NB_CAPTEUR_A_ADC] = {12, 13, 14, 2, 15, 10};
    uint8_t channels[NB_CAPTEUR_A_ADC] = {9,13,8,11,5,10,4,12,14,15}; // Les capteurs analogique doivent être définie dans le même ordre que les canaux dans ce tableau car sinon on ne récupérera pas les données dans le bon emplacement dans la mémoire

    uint16_t* data = AnalogSensor::initialiserADC(NB_CAPTEUR_A_ADC, channels);
    /// @warning ATTENTION, on doit avoir NB_CAPTEUR_A_ADC = nbSharp + nbUltrasound

    // On initialise le nombre de capteur de chaque type
    nbSharp = 10;
#ifdef ROBOTHW
    nbUltrasound = 0;
    nbLimitSwitch = 0;
    nbLigthBarrier = 0;
#endif

    //sharpNameVector = new SharpNameVector(nbSharp);
#ifdef ROBOTHW
    outputSensorVector = new OutputSensorVector(nbUltrasound);
    limitSwitchNameVector = new LimitSwitchNameVector(nbLimitSwitch);
    ligthBarrierNameVector = new LigthBarrierNameVector(nbLigthBarrier);
#endif

    // On initialise les tableaux de pointeur qui contiendront les capteurs
    sharps = new SharpSensor*[nbSharp];
    
    sharps[0] = new SharpSensor(SharpSensor::FRONT_LEFT, 9, data); // front left 9
    sharps[1] = new SharpSensor(SharpSensor::FRONT_RIGHT, 13, data); // front side right 13
    sharps[2] = new SharpSensor(SharpSensor::FRONT_SIDE_LEFT, 8, data); // front side left 8
    sharps[3] = new SharpSensor(SharpSensor::FRONT_SIDE_RIGHT, 11, data); // avant side droite 11
    sharps[4] = new SharpSensor(SharpSensor::BACK_LEFT, 5, data); // ARRIERE gauche 5
    sharps[5] = new SharpSensor(SharpSensor::BACK_MIDDLE, 10, data); // back middle 10
    sharps[6] = new SharpSensor(SharpSensor::BACK_RIGHT, 4, data); // arriere droit 4
    sharps[7] = new SharpSensor(SharpSensor::ELEVATOR_TOP, 12, data); // capteur haut ascenseur 12
    sharps[8] = new SharpSensor(SharpSensor::ELEVATOR_DOWN, 14, data); // capteur bas ascenseur 14
    sharps[9] = new SharpSensor(SharpSensor::NONE, 15, data); // rien
    //activeAllSharp();
#ifdef ROBOTHW
    ultrasounds = new UltrasoundSensor*[nbUltrasound];
    limitSwitchs = new  LimitSwitchSensor*[nbLimitSwitch];
#endif
    //ligthBarriers = new LigthBarrierSensor*[nbLigthBarrier];

    //On initialise les capteurs ayant besoin d'un ADC
    //ultrasounds[0] = new UltrasoundSensor(UltrasoundSensor::FRONT, 12, data);


#ifdef ROBOTHW
/*
#ifdef STM32F10X_CL
    //On initialise les autres capteurs
    //ligthBarriers[0] = new LigthBarrierSensor(LigthBarrierSensor::FRONT, GPIO_Pin_6, GPIOE);

    limitSwitchs[0] = new LimitSwitchSensor(LimitSwitchSensor::BACK_LEFT, GPIO_Pin_0, GPIOE);
    limitSwitchs[1] = new LimitSwitchSensor(LimitSwitchSensor::BACK_RIGHT, GPIO_Pin_1, GPIOE);
    limitSwitchs[2] = new LimitSwitchSensor(LimitSwitchSensor::FRONT, GPIO_Pin_2, GPIOE);
#endif
#ifdef STM32F10X_MD
    //On initialise les autres capteurs
    //ligthBarriers[0] = new LigthBarrierSensor(LigthBarrierSensor::FRONT, GPIO_Pin_2, GPIOA);

    limitSwitchs[0] = new LimitSwitchSensor(LimitSwitchSensor::BACK_LEFT, GPIO_Pin_9, GPIOC);
    limitSwitchs[1] = new LimitSwitchSensor(LimitSwitchSensor::BACK_RIGHT, GPIO_Pin_10, GPIOC);
    limitSwitchs[2] = new LimitSwitchSensor(LimitSwitchSensor::FRONT, GPIO_Pin_11, GPIOC);
#endif
*/
 //   AnalogSensor::initialiserADC_Fin(data, NB_CAPTEUR_A_ADC);
 #endif //ROBOTHW
}

Sensors::~Sensors()
{
    for (int i = 0; i< nbSharp; i++)
        delete sharps[i];
    for (int i = 0; i< nbUltrasound; i++)
        delete ultrasounds[i];
    #ifdef ROBOTHW
    for (int i = 0; i< nbLimitSwitch; i++)
        delete limitSwitchs[i];
    for (int i = 0; i< nbLigthBarrier; i++)
        delete ligthBarriers[i];
    #endif
    delete[] sharps;
    delete[] ultrasounds;
    #ifdef ROBOTHW
    delete[] limitSwitchs;
    delete[] ligthBarriers;
    #endif

    if (sharpNameVector)
        delete sharpNameVector;
    #ifdef ROBOTHW
    if (ligthBarrierNameVector)
        delete ligthBarrierNameVector;
    if (limitSwitchNameVector)
        delete limitSwitchNameVector;
    #endif
    if (outputSensorVector)
        delete outputSensorVector;
}

Sensors::SharpNameVector*  Sensors::detectedSharp()
{
    sharpNameVector->reset();
    for (int i = 0; i< nbSharp; i++)
    {
       if (sharps[i]->getValue().b)
       {
            sharpNameVector->push_back(sharps[i]->getName());
       }
    }
   // sharpNameVector->resize();
    return sharpNameVector;
}
#include "leds.h"
bool Sensors::sharpDetect()
{
    for (int i = 0; i< nbSharp; i++)
    {
        if (sharps[i]->getValue().b == true)
        {
            return true;
        }
    }
    return false; // Si aucun capteur n'a ce nom (exemple NONE)
}

bool Sensors::detectedSharp(SharpSensor::SharpName name)
{
    for (int i = 0; i< nbSharp; i++)
    {
        if (sharps[i]->getName() == name)
            return sharps[i]->getValue().b;
    }
    return false; // Si aucun capteur n'a ce nom (exemple NONE)
}

#ifdef ROBOTHW
Sensors::LimitSwitchNameVector* Sensors::detectedLimitSwitch()
{
    limitSwitchNameVector->reset();
    for (int i = 0; i<nbLimitSwitch; i++)
    {
        if (limitSwitchs[i]->getValue().b)
        {
            limitSwitchNameVector->push_back(limitSwitchs[i]->getName());
        }
    }
//    limitSwitchNameVector->resize();
    return limitSwitchNameVector;
}


Sensors::OutputSensorVector* Sensors::getValueUltrasound()
{
    outputSensorVector->reset();
    for (int i = 0; i < nbUltrasound; i++)
    {
        outputSensorVector->push_back(ultrasounds[i]->getValue());
    }
//    outputSensorVector->resize();
    return outputSensorVector;
}

#endif

Sensors* Sensors::getSensors()
{
    return Sensors::sensors;
}

SharpSensor** Sensors::getSharpSensorsList()
{
    return Sensors::sharps;
}

Sensors::OutputSensorVector* Sensors::getValueUltrasound(uint16_t distance)
{
    outputSensorVector->reset();
    for (int i = 0; i < nbUltrasound; i++)
    {
        Sensor::OutputSensor v = ultrasounds[i]->getValue();
         if (v.f < distance)
         {
             outputSensorVector->push_back(v);
         }
    }
//    outputSensorVector->resize();
    return outputSensorVector;
}


float Sensors::getValueUltrasound(UltrasoundSensor::UltrasoundName name)
{
    for (int i = 0; i < nbUltrasound; i++)
    {
        ultrasounds[i]->getValue();
         if (ultrasounds[i]->getName() == name)
         {
             return ultrasounds[i]->getValue().f;
         }
    }
    return -1;
}

#ifdef ROBOTHW
Sensors::LigthBarrierNameVector* Sensors::detectedLigthBarrier()
{
    ligthBarrierNameVector->reset();
    for (int i=0; i<nbLigthBarrier; i++)
    {
        if(ligthBarriers[i]->getValue().b)
        {
            ligthBarrierNameVector->push_back(ligthBarriers[i]->getName());
        }
    }
//    ligthBarrierNameVector->resize();
    return ligthBarrierNameVector;
}

bool Sensors::detectedLigthBarrier(LigthBarrierSensor::LigthBarrierName name)
{
    for (int i=0; i<nbLigthBarrier; i++)
    {
        if(ligthBarriers[i]->getName() == name)
        {
            return ligthBarriers[i]->getValue().b;
        }
    }
    return false; // Si aucun capteur n'a ce nom (exemple NONE)
}

#endif

void Sensors::update()
{
    for (int i=0; i<nbSharp; i++)
    {
        sharps[i]->updateValue();
    }
#ifdef ROBOTHW
    for (int i=0; i<nbLigthBarrier; i++)
    {
        ligthBarriers[i]->updateValue();
    }
    for (int i=0; i<nbLimitSwitch; i++)
    {
        limitSwitchs[i]->updateValue();
    }
#endif
    // Les autres n'ont pas besoin d'être mis à jour car on obtient la valeur directement en lisant la valeur de la pin
}

#ifdef ROBOTHW
bool Sensors::detectedLimitSwitch(LimitSwitchSensor::LimitSwitchName limitSwitchName)
{
    for (int i = 0; i<nbLimitSwitch; i++)
    {
        if (limitSwitchs[i]->getName() == limitSwitchName)
        {
            return limitSwitchs[i]->getValue().b;
        }
    }
    return false;
}
#endif

void Sensors::activeSharp(SharpSensor::SharpName name)
{
    for (int i=0; i<nbSharp;i++)
    {
        if (sharps[i]->getName() == name)
        {
            sharps[i]->setActif();
            break;
        }
    }
}

void Sensors::desactiveSharp(SharpSensor::SharpName name)
{
    for (int i=0; i<nbSharp;i++)
    {
        if (sharps[i]->getName() == name)
        {
            sharps[i]->unsetActif();
            break;
        }
    }
}
void Sensors::activeAllSharp()
{
    for (int i=0; i<nbSharp;i++)
    {
       sharps[i]->setActif();
    }
}

#ifndef ROBOTHW
void Sensors::keyPressEvent(QKeyEvent* evt, bool press)
{
    if(evt && evt->text() == "0" && !evt->isAutoRepeat())
    {
        if(press)
            sharps[0]->setEvent();
        else
            sharps[0]->unsetEvent();

    }
    if(evt && evt->text() == "1" && !evt->isAutoRepeat())
    {
        if(press)
            sharps[1]->setEvent();
        else
            sharps[1]->unsetEvent();

    }
    if(evt && evt->text() == "2" && !evt->isAutoRepeat())
    {
        if(press)
            sharps[2]->setEvent();
        else
            sharps[2]->unsetEvent();

    }
    if(evt && evt->text() == "3" && !evt->isAutoRepeat())
    {
        if(press)
            sharps[3]->setEvent();
        else
            sharps[3]->unsetEvent();

    }
    if(evt && evt->text() == "4" && !evt->isAutoRepeat())
    {
        if(press)
            sharps[4]->setEvent();
        else
            sharps[4]->unsetEvent();

    }
    if(evt && evt->text() == "5" && !evt->isAutoRepeat())
    {
        if(press)
            sharps[5]->setEvent();
        else
            sharps[5]->unsetEvent();

    }
    if(evt && evt->text() == "6" && !evt->isAutoRepeat())
    {
        if(press)
            sharps[6]->setEvent();
        else
            sharps[6]->unsetEvent();

    }
    if(evt && evt->text() == "7" && !evt->isAutoRepeat())
    {
        if(press)
            sharps[7]->setEvent();
        else
            sharps[7]->unsetEvent();

    }
    if(evt && evt->text() == "8" && !evt->isAutoRepeat())
    {
        if(press)
            sharps[8]->setEvent();
        else
            sharps[8]->unsetEvent();

    }
    if(evt && evt->text() == "9" && !evt->isAutoRepeat())
    {
        if(press)
            sharps[9]->setEvent();
        else
            sharps[9]->unsetEvent();

    }

}
#endif


