#ifndef SENSORS_H
#define SENSORS_H

#include "SharpSensor.h"
#include "UltrasoundSensor.h"
#include "LigthBarrierSensor.h"
#include "LimitSwitchSensor.h"
#include <vector>


/** @brief Classe permettant de gérer l'ensemble des capteurs du robot */
class Sensors
{
    public:
        /** @brief Constructeur de la classe */
        Sensors();
        /** @brief Desctucteur de la casse */
        virtual ~Sensors();
        /** @brief Vecteur de SharpSensor::SharpName */
        typedef std::vector<SharpSensor::SharpName> SharpNameVector;

        /** @brief Permet de vérifier si un capteur sharp quelconque a détecter un obstacle *
        *   @return Returne un SharpNameVector, vecteur contenant les SharpName des capteurs sharp renvoyant un true (donc ayant un obstacle devant eux). Si aucun capteur return un vector avec seulement NONE.  */
        SharpNameVector detectedSharp();
        /** @brief Permet de vérifier si un capteur sharp particulier a détecter un obstacle *
        *   @param name SharpName du capteur sharp dont on souhaite obtenir la valeur.  *
        *   @return True si un obstacle se trouve devant le capteur. */
        bool detectedSharp(SharpSensor::SharpName name);

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
