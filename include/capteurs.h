#ifndef CAPTEURS_H_INCLUDED
#define CAPTEURS_H_INCLUDED

#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"

/**@brief Classe gérant les capteurs infrarouges de distance. */
class Capteurs
{
private:
    uint16_t *data;
    uint32_t* output;
    uint16_t threshold;
    bool isConverted;
    void convertirDonnees();
public:
    Capteurs();
    /**@brief Enumération des différentes directions des capteurs. */
    enum Direction {AvantGauche=0, Derriere, Avant, AvantDroite};
    /**@brief Renvoie un booléen indiquant si la conversion est terminée. */
    bool conversionFinished();
    /**@brief Commence la conversion des canaux. */
    void startConversion();
    /**@brief Indique la présence (ou non) d'un obstacle dans une direction selon la valeur du threshold (= seuil).
     * @param Une des directions définies dans Capteurs::Direction
     * @return 0 ou 1
     */
    uint16_t getValue(Capteurs::Direction);
    /**@brief Nombre de canaux (= nombre de capteurs), a priori 4. */
    uint8_t NbrOfChannel;
};

#endif // CAPTEURS_H_INCLUDED
