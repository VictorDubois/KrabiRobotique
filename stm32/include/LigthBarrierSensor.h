#ifndef LIGTHBARRIERSENSOR_H
#define LIGTHBARRIERSENSOR_H

#include <Sensor.h>
#include "stm32f10x_gpio.h"

/** @brief Classe des gestions des barriers optiques */
class LigthBarrierSensor : public Sensor
{
    public:
        /** @brief Constructeur d'une barrière optique *
        *   @param pin Numéro de pin utilisée (GPIO_Pin_1, GPIO_Pin_2, ...) *
        *   @param group Groupe de pin utilisé (GPIOA, GPIOB, ...) */
        LigthBarrierSensor(uint16_t pin, GPIO_TypeDef* group);
        /** @brief Destructeur de la classe */
        virtual ~LigthBarrierSensor();

        /** @brief Permet de récupérer les données rendu diponible par le capteur fin de course*
        *   @return Retourne une structure OutputSensor contenant les données traitées du capteur. Cette structure sera de type LIGTH_BARRIER et la seul donnée utile sera donc la variable b qui contiendra un booléen valant true si le capteur détecte quelque chose. */
        OutputSensor getValue();
    protected:
    private:
        /** @brief Numéro de pin utilisée (GPIO_Pin_1, GPIO_Pin_2, ...) */
        uint16_t pin;
        /** @brief Groupe de pin utilisé (GPIOA, GPIOB, ...) */
        GPIO_TypeDef* group;
        /** @brief Compteur pour filtrer le signal numérique reçu. Ce compteur agit comme un filtre passe bas. */
        uint16_t counter;
};

#endif // LIGTHBARRIERSENSOR_H