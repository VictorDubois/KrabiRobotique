#ifndef SENSORS_H
#define SENSORS_H

#ifdef ROBOTHW

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
        /**@brief Vecteur de LigthBarrierSensor::LigthBarrierName */
        typedef vector<LigthBarrierSensor::LigthBarrierName> LigthBarrierNameVector;


        /** @brief Permet de vérifier si un capteur sharp quelconque a détecter un obstacle *
        *   @return Retourne un SharpNameVector, vecteur contenant les SharpName des capteurs sharp renvoyant un true (donc ayant un obstacle devant eux). Si aucun capteur returne un vector vide  */
        SharpNameVector* detectedSharp();
        /** @brief Permet de vérifier si un capteur sharp particulier a détecter un obstacle *
        *   @param name SharpName du capteur sharp dont on souhaite obtenir la valeur.  *
        *   @return True si un obstacle se trouve devant le capteur. */
        bool detectedSharp(SharpSensor::SharpName name);

        /** @brief Permet de vérifier si un fin de course quelconque est enclanché *
        *   @return Retourne un LimitSwitchNameVector, vecteur contenant les LimitSwitchName des capteurs fin de course renvoyant un true (donc étant enclanché). Si aucun capteur returne un vector vide.  */
        LimitSwitchNameVector* detectedLimitSwitch();
        /** @brief Permet de vérifier si un fin de course précis est enclanché *
        *   @return Retourne true si le capteur fin de course limitSwitch est enclanché
        *   @param limitSwitch Capteur fin de course que l'on souhaite tester*/
        bool detectedLimitSwitch(LimitSwitchSensor::LimitSwitchName limitSwitchName);

        /** @brief Permet de connaître la valeur de la distance de l'objet le plus proche de l'ensemble des capteurs ultrasons *
        *   @return Retourne un OutputSensorVector, vecteur contenant les valeurs de retour (dans un objet de type OutputSensor) de chaque capteurs ultrasons  */
        OutputSensorVector* getValueUltrasound();
        /** @brief Permet de connaître la valeur de la distance de l'objet le plus proche de l'ensemble des capteurs ultrasons qui détecte un objet à moins de X mm *
        *   @return Retourne un OutputSensorVector, vecteur contenant les valeurs de retour (dans un objet de type OutputSensor) de chaque capteurs ultrasons ayant un objet à moins de Xmm de lui
        *   @param  distance Distance en mm maximal que l'on souhaite avoir pour un objet devant les capteurs retournés  */
        OutputSensorVector* getValueUltrasound(uint16_t distance);
        /** @brief Permet de connaître la valeur de la distance de l'objet le plus d'un capteur ultrason précis *
        *   @return Retourne la distance en mm de l'objet le plus proche du capteur ayant pour nom name
        *   @param  name Nom du capteur dont on veut connaîte la distance en mm de l'objet le plus proche */
        float getValueUltrasound(UltrasoundSensor::UltrasoundName name);

        /** @brief Permet de vérifier si une barrière optique quelconque détecte un obstacle *
        *   @return Retourne un LigthBarrierNameVector, vecteur contenant les LigthBarrierName des barrières optiques renvoyant un true (donc ayant un obstacle devant eux). Si aucun capteur retourne un vector vide  */
        LigthBarrierNameVector* detectedLigthBarrier();
        /** @brief Permet de vérifier si une barrière optique quelconque détecte un obstacle *
        *   @return Retourne la valeur de la barrière optique ayant pour nom name  *
        *   @param name Nom de la barrière dont on veut connaître le nom */
        bool detectedLigthBarrier(LigthBarrierSensor::LigthBarrierName name);

        /** @brief Permet de connaîte l'adresse en mémoire de la seule et unique instance possible de cette classe */
        static Sensors* getSensors();

        /** @brief Permet de mettre à jour les valeurs des capteurs avant toute récupération (doit être lancé le plus souvant possible pour maintenir des valeurs cohérentes pour les capteurs dont la valeur de retour est filtré). */
        void update();

        /** @brief Delete tout les vectors créé par l'instance de cette classe */
        void deleteVectors();

        /** @brief Active le sharp qui a pour nom name
        *   @param name Nom du capteur qu'on souhaite activer */
        void activeSharp(SharpSensor::SharpName name);
        /** @brief Desactive le sharp qui a pour nom name
        *   @param name Nom du capteur qu'on souhaite désactiver */
        void desactiveSharp(SharpSensor::SharpName name);
        /** @brief Active tous les capteurs */
        void activeAllSharp();



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
        /** @brief Pointeur vers le dernier SharpNameVector définie */
        SharpNameVector* sharpNameVector;
        /** @brief Pointeur vers le dernier LimitSwitchNameVector définie */
        LimitSwitchNameVector* limitSwitchNameVector;
        /** @brief Pointeur vers le dernier LigthBarrierNameVector définie */
        LigthBarrierNameVector* ligthBarrierNameVector;
        /** @brief Pointeur vers le dernier OutputSensorVector définie */
        OutputSensorVector* outputSensorVector;

};

#endif

#endif // SENSORS_H
