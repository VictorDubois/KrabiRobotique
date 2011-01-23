#include "ValeursCapteurs.h"
#include <stdint.h>

ValeursCapteurs::ValeursCapteurs(uint16_t val_devant, uint16_t val_gauche, uint16_t val_droite, uint16_t val_derriere, uint16_t val_seuil):
    devant(val_devant),
    gauche(val_gauche),
    droite(val_droite),
    derriere(val_derriere),
    seuil(val_seuil)
{}


