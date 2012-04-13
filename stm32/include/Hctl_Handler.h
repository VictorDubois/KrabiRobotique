#ifdef RIEN_A_FAIRE
#ifndef HCTL_HANDLER_H_INCLUDED
#define HCTL_HANDLER_H_INCLUDED

#include "variable.h"
#include <stdint.h>
//#include "ValeursRoues.h"
#include "stm32f10x_gpio.h"
#include "Position.h"
#include "stm32f10x_rcc.h"

/**@brief (Jamais utilisée...)Classe faisant l'interface entre le STM et la carte HCTL pour le compte de la classe AsservissementHandler.*/
class Hctl_Handler
{

    public:
			/**@brief constructeur définissant les PIN utilisé, les types d'entrée et sorties, propage l'horloge et initialise les valeurs des PIN. */
            Hctl_Handler();
            /**@brief destructeur de la classe. */
            ~Hctl_Handler();
            //ValeursRoues faireUnTour();
            /**@brief A partir de 4 nombre sur 8 bit, ceux ci sont concaténé pour former un entier sur 32 bits */
            uint32_t reconstituerCompteur(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
            /**@brief à partir de 8 bits, cette fonction renvoi un octet. */
            uint8_t reconstituerOctet(uint8_t a, uint8_t b, uint8_t c, uint8_t d,  uint8_t e,  uint8_t f,  uint8_t g,  uint8_t h);
    private:
            //ValeursRoues roues;
            uint32_t regarderRoue(BitAction valeurPinXY);
			/**@brief donne un octet du compteur */
            uint8_t Pina();
            /**@brief Laisse le temps au microcontrolleur de modifier les valeurs des pin avant de lancer pina() */
            uint8_t Get_hi();
};

#endif // HCTLHANDLER_H_INCLUDED
#endif
