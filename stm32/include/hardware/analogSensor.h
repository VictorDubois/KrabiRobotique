#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "sensor.h"
#include <stdint.h>

#ifdef ROBOTHW // pour le vrai robot
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#else
//#include <stdlib.h>
#endif

/// @brief Classe abstraite de gestion des capteurs analogiques
class AnalogSensor : public Sensor
{
    public:
        /** @brief Constructeur d'un capteur analogique de base *
        *   @param Channel Numéro du canal du convertisseur analogiqueNumérique utilisé *
        *   @param pData Pointeur vers le tableau de données brutes des capteur directement sortie du ADC. Ce pointeur doit bien pointer vers la première case du tableau et pas vers la case de données brutes utile de ce capteur.  */
        AnalogSensor(uint8_t channel, uint16_t* pData);

        /** @brief Destructeur de la classe */
        virtual ~AnalogSensor();

        /** @brief Permet de récupérer les données rendu diponible par le capteur*
        *   @return Retourne une structure OutputSensor contenant les données traitées du capteur */
        virtual OutputSensor getValue() = 0;

        /** @brief Methode de classe permettant d'initialiser la convertion ADC du stm32. Cette méthode doit seulement être appelé une seule fois avant toutes déclarration d'un objet de classe héritant d'AnalogSensor*
        *   @warning Attention, cette methode devrait être appelé qu'une seule et unique fois avant toutes déclaration d'un objet de classe héritant d'AnalogSensor. *
        *   @param nbChannelADC Nombre de canal ADC utilisé au total *
        *   @return Pointeur vers le tableau de d'uint16_t dans lequel sera stocké les données numériques brute sortie du convertisseur analogique numérique. */
        static uint16_t* initialiserADC(uint8_t nbChannel, uint8_t* channels);

        /** @brief Permet de lancer la convertion des données sur le ADC */
        static void startConversion();

        /** @brief Permet de savoir si la convertion est finie ou non */
        static bool conversionFinished();

    protected:

        /** @brief Numéro du canal du convertisseur analogiqueNumérique utilisé */
        uint8_t channel;

        /** @brief Pointeur vers la case de données brutes du capteur directement sortie du ADC */
        uint16_t* data;

    private:

        static int nbCapteurDejaInitialise;

};

#endif // ANALOGSENSOR_H
