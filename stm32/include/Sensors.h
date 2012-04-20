#ifndef SENSORS_H
#define SENSORS_H

#include "SharpSensor.h"
#include "UltrasoundSensor.h"
#include "LigthBarrierSensor.h"
#include "LimitSwitchSensor.h"
#include "vector.h"


/** @brief Classe permettant de gérer l'ensemble des capteurs du robot
*   @warning Une seul instance de cette classe ne doit être définie */
class Sensors
{
    public:
        /** @brief Constructeur de la classe */
        Sensors();
        /** @brief Desctucteur de la casse */
        virtual ~Sensors();

        /** @brief Vecteur de SharpSensor::SharpName */
        typedef vector<SharpSensor::SharpName> SharpNameVector;
        /**@brief Vecteur de LimitSwitchSensor::LimitSwitchName */
        typedef vector<LimitSwitchSensor::LimitSwitchName> LimitSwitchNameVector;
        /**@brief Vecteur de Sensor::OutputSensor */
        typedef vector<Sensor::OutputSensor> OutputSensorVector;


        /** @brief Permet de vérifier si un capteur sharp quelconque a détecter un obstacle *
        *   @return Returne un SharpNameVector, vecteur contenant les SharpName des capteurs sharp renvoyant un true (donc ayant un obstacle devant eux). Si aucun capteur returne un vector vide  */
        SharpNameVector detectedSharp();
        /** @brief Permet de vérifier si un capteur sharp particulier a détecter un obstacle *
        *   @param name SharpName du capteur sharp dont on souhaite obtenir la valeur.  *
        *   @return True si un obstacle se trouve devant le capteur. */
        bool detectedSharp(SharpSensor::SharpName name);

        /** @brief Permet de vérifier si un fin de course quelconque est enclanché *
        *   @return Returne un LimitSwitchNameVector, vecteur contenant les LimitSwitchName des capteurs fin de course renvoyant un true (donc étant enclanché). Si aucun capteur returne un vector vide.  */
        LimitSwitchNameVector detectedLimitSwitch();

        /** @brief Permet de connaître la valeur de la distance de l'objet le plus proche de l'ensemble des capteurs ultrasons *
        *   @return Retourne un OutputSensorVector, vecteur contenant les valeurs de retour (dans un objet de type OutputSensor) de chaque capteurs ultrasons  */
        OutputSensorVector getValueUltrasound();
        /** @brief Permet de connaître la valeur de la distance de l'objet le plus proche de l'ensemble des capteurs ultrasons qui détecte un objet à moins de X mm *
        *   @return Retourne un OutputSensorVector, vecteur contenant les valeurs de retour (dans un objet de type OutputSensor) de chaque capteurs ultrasons ayant un objet à moins de Xmm de lui
        *   @param  distance Distance en mm maximal que l'on souhaite avoir pour un objet devant les capteurs retournés  */
        OutputSensorVector getValueUltrasound(uint16_t distance);
        /** @brief Permet de connaître la valeur de la distance de l'objet le plus d'un capteur ultrason précis *
        *   @return Retourne la distance en mm de l'objet le plus proche du capteur ayant pour nom name
        *   @param  name Nom du capteur dont on veut connaîte la distance en mm de l'objet le plus proche */
        float getValueUltrasound(UltrasoundSensor::UltrasoundName name);



        /** @brief Permet de connaîte l'adresse en mémoire de la seule et unique instance possible de cette classe */
        static Sensors* getSensors();


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
        /** @brief Attribue de classe permettant de connaîte l'adresse en mémoire de la seule et unique instance possible de cette classe */
        static Sensors* sensors;
};

#endif // SENSORS_H
