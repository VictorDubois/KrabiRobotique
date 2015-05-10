#include "command.h"

// fait un virage d'un certain angle à la vitesse max suivant un certain rayon de courbure
// arrive avec un certaine vitesse de fin
// marche que vers l'avant
class CommandVirage : public Command
{
public:
    // rayon > 0
    // angle > 0 : vers la gauche, angle < 0 : vers la droite
    CommandVirage(float rayon, float angle, float vitesseLineaireMax = VITESSE_LINEAIRE_MAX, float vitesseFin = 0.0f);

    virtual void update();

private:
    float rayonCourbure, angleVise, vitesseLinMax;
    float vFin2; // vitesse finale * vitesse finale
};
