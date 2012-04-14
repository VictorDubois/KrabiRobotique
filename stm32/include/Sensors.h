#ifndef SENSORS_H
#define SENSORS_H

#include "SharpSensor.h"
#include "UltrasoundSensor.h"
#include "LigthBarrierSensor.h"
#include "LimitSwitchSensor.h"

/** @brief Classe permettant de gérer l'ensemble des capteurs du robot */
class Sensors
{
    public:
        /** @brief Constructeur de la classe */
        Sensors();
        /** @brief Desctucteur de la casse */
        virtual ~Sensors();
    protected:
    private:
        /** @brief Tableau des capteurs sharps */
        SharpSensor** sharps;
        /** @brief Nombre de capteurs sharps */
        int nbSharp;
        /** @brief Tableau des capteurs ultrason */
        UltrasoundSensor** ultrasounds;
        /** @brief Nombre d'ultrason */
        int nbUltrasound;
        /** @brief Tableau des barrières optiques */
        LigthBarrierSensor** ligthBarriers;
        /** @brief Nombre de barrières optiques */
        int nbLigthBarrier;
        /** @brief Tableau des fin de course */
        LimitSwitchSensor** limitSwitchs;
        /** @brief Nombre de capteurs fin de course */
        int nbLimitSwitch;
};

#endif // SENSORS_H
