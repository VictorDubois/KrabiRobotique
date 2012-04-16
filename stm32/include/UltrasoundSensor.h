#ifndef ULTRASOUNDSENSOR_H
#define ULTRASOUNDSENSOR_H

#include <AnalogSensor.h>
#include "variable.h"

/** @brief Classe des gestions des capteurs ultrasons */
class UltrasoundSensor : public AnalogSensor
{
    public:
        /** @brief Constructeur d'un capteur ultrason *
        *   @param channel Canal de l'ADC utilisé pour ce capteur. *
        *   @param pData Pointeur vers les données brutes du capteur directement sortie de l'ADC*/
        UltrasoundSensor(uint8_t channel, uint16_t* pData);
        /** @brief Destructeur de cette classe */
        virtual ~UltrasoundSensor();

        /** @brief Permet de récupérer les données rendu diponible par le capteur ultrason*
        *   @return Retourne une structure OutputSensor contenant les données traitées du capteur. Cette structure sera de type ULTRASOUND et la seul donnée utile sera donc la variable f qui contiendra la distance en mm du premier obstacle. */
        OutputSensor getValue();

        /** @brief Coefficient utilisé pour transformé la valeur numérique obtenu en sortie de l'ADC en une distance en mm. */
        static float coeff;
    protected:
    private:

};

#endif // ULTRASOUNDSENSOR_H
