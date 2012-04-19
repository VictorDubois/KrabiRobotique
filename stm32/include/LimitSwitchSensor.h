#ifndef LIMITSWITCHSENSOR_H
#define LIMITSWITCHSENSOR_H

#include <Sensor.h>
#include "stm32f10x_gpio.h"

/** @brief Classe des gestions des capteurs fin de course */
class LimitSwitchSensor : public Sensor
{
    public:
        /** @brief Permet de nommer les différents fin de course */
        enum LimitSwitchName {
            /** @brief Aucun capteur */
            NONE,
            /** @brief Fin de course arrière gauche */
            BACK_LEFT,
            /** @brief Fin de course arrière droit */
            BACK_RIGTH,
            /** @brief Fin de course avant */
            FRONT
        };
        /** @brief Permet de nommer les différents fin de course */
        typedef enum LimitSwitchName LimitSwitchName;

        /** @brief Constructeur d'un capteur fin de course *
        *   @param name Nom du fin de course *
        *   @param pin Numéro de pin utilisée (GPIO_Pin_1, GPIO_Pin_2, ...) *
        *   @param group Groupe de pin utilisé (GPIOA, GPIOB, ...) */
        LimitSwitchSensor(LimitSwitchName name, uint16_t pin, GPIO_TypeDef* group);
        /** @brief Destructeur de la classe */
        virtual ~LimitSwitchSensor();

        /** @brief Permet de récupérer les données rendu diponible par le capteur fin de course*
        *   @return Retourne une structure OutputSensor contenant les données traitées du capteur. Cette structure sera de type LIMIT_SWITCH et la seul donnée utile sera donc la variable b qui contiendra un booléen valant true si le capteur est enclanché. */
        OutputSensor getValue();
        /** @brief Accesseur de name */
        LimitSwitchName getName();
    protected:
    private:
        /** @brief Numéro de pin utilisée (GPIO_Pin_1, GPIO_Pin_2, ...) */
        uint16_t pin;
        /** @brief Groupe de pin utilisé (GPIOA, GPIOB, ...) */
        GPIO_TypeDef* group;
        /** @brief Compteur pour filtrer le signal numérique reçu. Ce compteur agit comme un filtre passe bas. */
        uint16_t counter;
        /** @brief Nom du fin de course */
        LimitSwitchName name;
};

#endif // LIMITSWITCHSENSOR_H