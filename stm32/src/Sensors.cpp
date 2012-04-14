#include "Sensors.h"

Sensors::Sensors()
{
    uint16_t* data = AnalogSensor::initialiserADC(NB_CAPTEUR_A_ADC);
    /// @warning ATTENTION, on doit avoir NB_CAPTEUR_A_ADC = nbSharp + nbUltrasound

    nbSharp = 5;
    nbUltrasound = 1;
    nbLimitSwitch = 4;
    nbLigthBarrier = 1;

    sharps = new SharpSensor*[nbSharp];
    ultrasounds = new UltrasoundSensor*[nbUltrasound];
    limitSwitchs = new  LimitSwitchSensor*[nbLimitSwitch];
    ligthBarriers = new LigthBarrierSensor*[nbLigthBarrier];

    //TODO à finir
}

Sensors::~Sensors()
{
    //dtor
}
