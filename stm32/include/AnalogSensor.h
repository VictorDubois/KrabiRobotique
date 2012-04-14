#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include <Sensor.h>
#include <stdint.h>
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"

/** @brief Classe abstraite de gestion des capteurs analogiques */
class AnalogSensor : public Sensor
{
    public:
        /** @brief Constructeur d'un capteur analogique de base *
        *   @param Channel Numéro du canal du convertisseur analogiqueNumérique utilisé *
        *   @param pData Pointeur vers les données brutes du capteur directement sortie du ADC */
        AnalogSensor(uint8_t channel, uint16_t* pData);
        /** @brief Destructeur de la classe */
        virtual ~AnalogSensor();
        /** @brief Permet de récupérer les données rendu diponible par le capteur*
        *   @return Retourne une structure OutputSensor contenant les données traitées du capteur */
        virtual OutputSensor getValue() = 0;

        /** @brief Methode de classe permettant d'initialiser la convertion ADC du stm32. Cette méthode doit seulement être appelé une seule fois *
        *   @warning Attention, cette methode devrait être appelé qu'une seule et unique fois. *
        *   @param nbChannelADC Nombre de canal ADC utilisé au total *
        *   @return Pointeur vers le tableau de d'uint16_t dans lequel sera stocké les données numériques brute sortie du convertisseur analogique numérique. */
        static uint16_t* initialiserADC(int nbChannel);

    protected:
        /** @brief Numéro du canal du convertisseur analogiqueNumérique utilisé */
        uint8_t channel;
        /** @brief Pointeur vers les données brutes du capteur directement sortie du ADC */
        uint16_t* data;
    private:
};

#endif // ANALOGSENSOR_H
