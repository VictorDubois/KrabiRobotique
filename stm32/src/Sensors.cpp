#include "Sensors.h"

Sensors::Sensors()
{
    uint16_t* data = AnalogSensor::initialiserADC_Debut(NB_CAPTEUR_A_ADC);
    /// @warning ATTENTION, on doit avoir NB_CAPTEUR_A_ADC = nbSharp + nbUltrasound

    // On initialise le nombre de capteur de chaque type
    nbSharp = 5;
    nbUltrasound = 1;
    nbLimitSwitch = 4;
    nbLigthBarrier = 1;

    // On initialise les tableaux de pointeur qui contiendront les capteurs
    sharps = new SharpSensor*[nbSharp];
    ultrasounds = new UltrasoundSensor*[nbUltrasound];
    limitSwitchs = new  LimitSwitchSensor*[nbLimitSwitch];
    ligthBarriers = new LigthBarrierSensor*[nbLigthBarrier];

    //On initialise les capteurs ayant besoin d'un ADC
    ultrasounds[0] = new UltrasoundSensor(10, data);

    sharps[0] = new SharpSensor(11, data);
    sharps[1] = new SharpSensor(12, data);
    sharps[2] = new SharpSensor(13, data);
    sharps[3] = new SharpSensor(14, data);
    sharps[4] = new SharpSensor(15, data);

    //On initialise les autres capteurs
    ligthBarriers[0] = new LigthBarrierSensor(GPIO_Pin_6, GPIOE);

    limitSwitchs[0] = new LimitSwitchSensor(GPIO_Pin_0, GPIOE);
    limitSwitchs[1] = new LimitSwitchSensor(GPIO_Pin_1, GPIOE);
    limitSwitchs[2] = new LimitSwitchSensor(GPIO_Pin_2, GPIOE);
    limitSwitchs[3] = new LimitSwitchSensor(GPIO_Pin_3, GPIOE);

    AnalogSensor::initialiserADC_Fin(data, NB_CAPTEUR_A_ADC);
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
}
