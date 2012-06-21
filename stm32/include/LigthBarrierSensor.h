#ifndef LIGTHBARRIERSENSOR_H
#define LIGTHBARRIERSENSOR_H

#include <Sensor.h>
#ifdef ROBOTHW
    #include "stm32f10x_gpio.h"
#endif

/** @brief Classe des gestions des barriers optiques */
class LigthBarrierSensor : public Sensor
{
    #ifndef ROBOTHW
    typedef int GPIO_TypeDef;
    #endif
    public:

        /** @brief Permet de nommer les différentes barrières optique */
        enum LigthBarrierName {
            /** @brief Aucun capteur */
            NONE,
            /** @brief barrière optique avant */
            FRONT
        };
        /** @brief Permet de nommer les différents fin de course */
        typedef enum LigthBarrierName LigthBarrierName;

        #ifdef ROBOTHW
        /** @brief Constructeur d'une barrière optique *
        *   @param pin Numéro de pin utilisée (GPIO_Pin_1, GPIO_Pin_2, ...) *
        *   @param group Groupe de pin utilisé (GPIOA, GPIOB, ...) *
        *   @brief name Nom de la barrière optique */
        LigthBarrierSensor(LigthBarrierName name, uint16_t pin, GPIO_TypeDef* group);
        #else
        LigthBarrierSensor();
        #endif
        /** @brief Destructeur de la classe */
        virtual ~LigthBarrierSensor();

        /** @brief Permet de récupérer les données rendu diponible par le capteur fin de course*
        *   @return Retourne une structure OutputSensor contenant les données traitées du capteur. Cette structure sera de type LIGTH_BARRIER et la seul donnée utile sera donc la variable b qui contiendra un booléen valant true si le capteur détecte quelque chose. */
        OutputSensor getValue();
        /** @brief Accesseur de l'attribue name */
        LigthBarrierName getName();

        /** @brief Met à jour la valeur de retour du capteur en étidiant la valeur actuel sur la pin sur laquel il est branché. *
        *   @warning Il faut appeler cette fonction souvent pour que la value du retour du capteur soit la plus juste possible. */
        void updateValue();

    protected:
    private:
    #ifdef ROBOTHW
        /** @brief Numéro de pin utilisée (GPIO_Pin_1, GPIO_Pin_2, ...) */
        uint16_t pin;
        /** @brief Groupe de pin utilisé (GPIOA, GPIOB, ...) */
        GPIO_TypeDef* group;
        /** @brief Compteur pour filtrer le signal numérique reçu. Ce compteur agit comme un filtre passe bas. */
        uint16_t counter;
        /** @brief Nom de la barrière optique */
        LigthBarrierName name;
        /** @brief Valeur retourné par le capteur */
        bool output;
    #endif
};

#endif // LIGTHBARRIERSENSOR_H
