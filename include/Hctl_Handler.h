#ifndef HCTL_HANDLER_H_INCLUDED
#define HCTL_HANDLER_H_INCLUDED

#include <stdint.h>
#include "ValeursRoues.h"
#include "stm32f10x_gpio.h"

enum coteRoue{
 ROUE_GAUCHE = Bit_SET,
 ROUE_DROITE = Bit_RESET
};

/**@brief Classe faisant l'interface entre le STM et la carte HCTL pour le compte de la classe AsservissementHandler.*/
class Hctl_Handler
{

    public:
            Hctl_Handler();
            ~Hctl_Handler();
            ValeursRoues faireUnTour();
            uint32_t reconstituerCompteur(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
            uint8_t reconstituerOctet(uint8_t a, uint8_t b, uint8_t c, uint8_t d,  uint8_t e,  uint8_t f,  uint8_t g,  uint8_t h);
    private:
            //uint32_t etatPC10;
            //uint32_t etatPC11;
            ValeursRoues roues;
            uint32_t regarderRoue(BitAction valeurPinXY);
            uint8_t Pina();
            uint8_t Get_hi();
};

#endif // HCTLHANDLER_H_INCLUDED
