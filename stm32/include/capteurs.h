#ifndef CAPTEURS_H_INCLUDED
#define CAPTEURS_H_INCLUDED

#include "variable.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"

/**@brief Classe gérant les capteurs infrarouges de distance. */
class Capteurs
{
private:
    /**@brief Nombre de canaux (= nombre de capteurs), a priori 5. */
    uint8_t NbrOfChannel;
    /**@brief Tableau de stockage des données brut envoyées par les capteurs. */
    uint16_t *data;
    /**@brief Tableau de stockage de la présence ou non d'un objet devant un capteur. */
    uint32_t* output;
    /**@brief Seuil de détection d'un objet. */
    uint16_t threshold;
    /**@brief Est ce que la conversion à eu lieu? */
    bool isConverted;
    /**@brief Convertie les données brut en données vérifié (passe de data à output)*/
    void convertirDonnees();
public:
    /**@brief Définie les capteurs et met les sorties dans output[]. Il faut donc modifier cette fonction si vous voulez modifier les capteurs présents. */
    Capteurs();
    /**@brief Enumération des différentes directions des capteurs. */
     enum Direction {AvantDroitInt=0, AvantDroitExt, Derriere, AvantGaucheInt,SurPince,AvantGaucheExt};
    /**@brief Renvoie un booléen indiquant si la conversion est terminée. */
    bool conversionFinished();
    /**@brief Commence la conversion des canaux. */
    void startConversion();
    /**@brief Indique la présence (ou non) d'un obstacle dans une direction selon la valeur du threshold (= seuil).
     * @param Capteurs::Direction Une des directions définies dans Capteurs::Direction
     * @return 0 ou 1
     */
    uint16_t getValue(Capteurs::Direction);
    /**@brief Retourne le nombre de canaux. */
    uint8_t getNbrOfChannel();
};

#endif // CAPTEURS_H_INCLUDED
