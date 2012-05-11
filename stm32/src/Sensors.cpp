#include "Sensors.h"

#ifdef ROBOTHW

Sensors* Sensors::sensors = NULL;

Sensors::Sensors()
{
    Sensors::sensors = this;
    uint8_t channels[NB_CAPTEUR_A_ADC] = {12, 13, 14, 2, 15, 11}; // Les capteurs analogique doivent être définie dans le même ordre que les canaux dans ce tableau car sinon on ne récupérera pas les données dans le bon emplacement dans la mémoire
    uint16_t* data = AnalogSensor::initialiserADC(NB_CAPTEUR_A_ADC, channels);
    /// @warning ATTENTION, on doit avoir NB_CAPTEUR_A_ADC = nbSharp + nbUltrasound

    // On initialise le nombre de capteur de chaque type
    nbSharp = 4;
    nbUltrasound = 1;
    nbLimitSwitch = 3;
    nbLigthBarrier = 0;

    sharpNameVector = NULL;
    outputSensorVector = NULL;
    limitSwitchNameVector = NULL;
    ligthBarrierNameVector = NULL;

    // On initialise les tableaux de pointeur qui contiendront les capteurs
    sharps = new SharpSensor*[nbSharp];
    ultrasounds = new UltrasoundSensor*[nbUltrasound];
    limitSwitchs = new  LimitSwitchSensor*[nbLimitSwitch];
    //ligthBarriers = new LigthBarrierSensor*[nbLigthBarrier];

    //On initialise les capteurs ayant besoin d'un ADC
    ultrasounds[0] = new UltrasoundSensor(UltrasoundSensor::FRONT, 12, data);


    sharps[0] = new SharpSensor(SharpSensor::FRONT_LEFT, 13, data);
    sharps[1] = new SharpSensor(SharpSensor::FRONT_RIGTH, 14, data);
    sharps[2] = new SharpSensor(SharpSensor::LEFT, 2, data);
    sharps[3] = new SharpSensor(SharpSensor::RIGTH, 15, data);
    sharps[4] = new SharpSensor(SharpSensor::BACK, 11, data);

#ifdef STM32F10X_CL
    //On initialise les autres capteurs
    //ligthBarriers[0] = new LigthBarrierSensor(LigthBarrierSensor::FRONT, GPIO_Pin_6, GPIOE);

    limitSwitchs[0] = new LimitSwitchSensor(LimitSwitchSensor::BACK_LEFT, GPIO_Pin_0, GPIOE);
    limitSwitchs[1] = new LimitSwitchSensor(LimitSwitchSensor::BACK_RIGTH, GPIO_Pin_1, GPIOE);
    limitSwitchs[2] = new LimitSwitchSensor(LimitSwitchSensor::FRONT, GPIO_Pin_2, GPIOE);
#endif
#ifdef STM32F10X_MD
    //On initialise les autres capteurs
    //ligthBarriers[0] = new LigthBarrierSensor(LigthBarrierSensor::FRONT, GPIO_Pin_2, GPIOA);

    limitSwitchs[0] = new LimitSwitchSensor(LimitSwitchSensor::BACK_LEFT, GPIO_Pin_9, GPIOC);
    limitSwitchs[1] = new LimitSwitchSensor(LimitSwitchSensor::BACK_RIGTH, GPIO_Pin_10, GPIOC);
    limitSwitchs[2] = new LimitSwitchSensor(LimitSwitchSensor::FRONT, GPIO_Pin_11, GPIOC);
#endif


 //   AnalogSensor::initialiserADC_Fin(data, NB_CAPTEUR_A_ADC);
}

Sensors::~Sensors()
{
    for (int i = 0; i< nbSharp; i++)
        delete sharps[i];
    for (int i = 0; i< nbUltrasound; i++)
        delete ultrasounds[i];
    for (int i = 0; i< nbLimitSwitch; i++)
        delete limitSwitchs[i];
    for (int i = 0; i< nbLigthBarrier; i++)
        delete ligthBarriers[i];
    delete[] sharps;
    delete[] ultrasounds;
    delete[] limitSwitchs;
    delete[] ligthBarriers;

    if (sharpNameVector)
        delete sharpNameVector;
    if (ligthBarrierNameVector)
        delete ligthBarrierNameVector;
    if (limitSwitchNameVector)
        delete limitSwitchNameVector;
    if (outputSensorVector)
        delete outputSensorVector;
}

Sensors::SharpNameVector*  Sensors::detectedSharp()
{
    if (sharpNameVector)
        delete sharpNameVector;
    sharpNameVector = new SharpNameVector(nbSharp);
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

bool Sensors::detectedSharp(SharpSensor::SharpName name)
{
    for (int i = 0; i< nbSharp; i++)
    {
        if (sharps[i]->getName() == name)
            return sharps[i]->getValue().b;
    }
    return false; // Si aucun capteur n'a ce nom (exemple NONE)
}

Sensors::LimitSwitchNameVector* Sensors::detectedLimitSwitch()
{
    if (limitSwitchNameVector)
        delete limitSwitchNameVector;
    limitSwitchNameVector = new LimitSwitchNameVector(nbLimitSwitch);
    for (int i = 0; i<nbLimitSwitch; i++)
    {
        if (limitSwitchs[i]->getValue().b)
        {
            limitSwitchNameVector->push_back(limitSwitchs[i]->getName());
        }
    }
    limitSwitchNameVector->resize();
    return limitSwitchNameVector;
}


Sensors::OutputSensorVector* Sensors::getValueUltrasound()
{
    if (outputSensorVector)
        delete outputSensorVector;
    outputSensorVector = new OutputSensorVector(nbUltrasound);
    for (int i = 0; i < nbUltrasound; i++)
    {
        outputSensorVector->push_back(ultrasounds[i]->getValue());
    }
    outputSensorVector->resize();
    return outputSensorVector;
}

Sensors* Sensors::getSensors()
{
    return Sensors::sensors;
}

Sensors::OutputSensorVector* Sensors::getValueUltrasound(uint16_t distance)
{
    if (outputSensorVector)
        delete outputSensorVector;
    outputSensorVector = new OutputSensorVector(nbUltrasound);
    for (int i = 0; i < nbUltrasound; i++)
    {
        Sensor::OutputSensor v = ultrasounds[i]->getValue();
         if (v.f < distance)
         {
             outputSensorVector->push_back(v);
         }
    }
    outputSensorVector->resize();
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

Sensors::LigthBarrierNameVector* Sensors::detectedLigthBarrier()
{
    if (ligthBarrierNameVector)
        delete ligthBarrierNameVector;
    ligthBarrierNameVector = new LigthBarrierNameVector(nbLigthBarrier);
    for (int i=0; i<nbLigthBarrier; i++)
    {
        if(ligthBarriers[i]->getValue().b)
        {
            ligthBarrierNameVector->push_back(ligthBarriers[i]->getName());
        }
    }
    ligthBarrierNameVector->resize();
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


void Sensors::update()
{
    for (int i=0; i<nbSharp; i++)
    {
        sharps[i]->updateValue();
    }
    for (int i=0; i<nbLigthBarrier; i++)
    {
        ligthBarriers[i]->updateValue();
    }
    for (int i=0; i<nbLimitSwitch; i++)
    {
        limitSwitchs[i]->updateValue();
    }
    // Les autres n'ont pas besoin d'être mis à jour car on obtient la valeur directement en lisant la valeur de la pin
}

#endif //ROBOTHW
