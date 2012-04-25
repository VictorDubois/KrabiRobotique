#ifndef ULTRASOUNDSENSOR_H
#define ULTRASOUNDSENSOR_H

#ifdef ROBOTHW


#include <AnalogSensor.h>
#include "variable.h"

/** @brief Classe des gestions des capteurs ultrasons */
class UltrasoundSensor : public AnalogSensor
{
    public:
        /** @brief Permet de nommer les différents capteurs */
        enum UltrasoundName
        {
            /** @brief Aucun capteur */
            NONE,
            /** @brief Capteur avant */
            FRONT
        };
        /** @brief Permet de nommer les différents capteurs */
        typedef enum UltrasoundName UltrasoundName;

        /** @brief Constructeur d'un capteur ultrason *
        *   @param channel Canal de l'ADC utilisé pour ce capteur. *
        *   @param pData Pointeur vers les données brutes du capteur directement sortie de l'ADC*/
        UltrasoundSensor(UltrasoundName name, uint8_t channel, uint16_t* pData);
        /** @brief Destructeur de cette classe */
        virtual ~UltrasoundSensor();

        /** @brief Accesseur de name */
        UltrasoundName getName();

        /** @brief Permet de récupérer les données rendu diponible par le capteur ultrason*
        *   @return Retourne une structure OutputSensor contenant les données traitées du capteur. Cette structure sera de type ULTRASOUND et la seul donnée utile sera donc la variable f qui contiendra la distance en mm du premier obstacle. */
        OutputSensor getValue();

        /** @brief Coefficient utilisé pour transformé la valeur numérique obtenu en sortie de l'ADC en une distance en mm. */
        static float coeff;
    protected:
    private:
        UltrasoundName name;

};

#enfif

#endif // ULTRASOUNDSENSOR_H
