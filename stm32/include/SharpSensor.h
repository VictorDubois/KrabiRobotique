#ifndef SHARPSENSOR_H
#define SHARPSENSOR_H

#include <AnalogSensor.h>
#include "variable.h"

/** @brief Classe des gestions des capteurs sharps */
class SharpSensor : public AnalogSensor
{
    public:
        /** @brief Constructeur d'un capteur sharp *
        *   @param channel Canal de l'ADC utilisé pour ce capteur. *
        *   @param pData Pointeur vers les données brutes du capteur directement sortie du ADC*/
        SharpSensor(uint8_t channel, uint16_t* pData);
        /** @brief Destructeur de cette classe */
        virtual ~SharpSensor();
        /** @brief Permet de récupérer les données rendu diponible par le capteur sharp*
        *   @return Retourne une structure OutputSensor contenant les données traitées du capteur. Cette structure sera de type SHARP et la seul donnée utile sera donc la variable b qui sera a true si un obstacle est devant le capteur sharp, false sinon. */
        OutputSensor getValue();

        /** @brief Seuil de détection utilisé pour les calibrer les capteurs sharp. Un retour supérieur à ce seuil sera considéré comme la détection d'un obstacle */
        static uint16_t threshold;
    protected:
    private:
        /** @brief Compteur pour filtrer le signal numérique reçu. Ce compteur agit comme un filtre passe bas. */
        uint32_t counter;
};

#endif // SHARPSENSOR_H
