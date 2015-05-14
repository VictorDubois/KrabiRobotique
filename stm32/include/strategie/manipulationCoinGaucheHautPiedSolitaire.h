#ifndef MANIPULATION_COIN_GAUCHE_HAUT_PIED_SOLITAIRE_H
#define MANIPULATION_COIN_GAUCHE_HAUT_PIED_SOLITAIRE_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class ManipulationCoinGaucheHautPiedSolitaire : public MediumLevelAction
{
    public :
        ManipulationCoinGaucheHautPiedSolitaire(Position positionDepart, bool isYellow);
        ~ManipulationCoinGaucheHautPiedSolitaire();
        int update();
        Etape::EtapeType getType();

    private :
        bool isYellow;
};

#endif // MANIPULATION_COIN_GAUCHE_HAUT_PIED_SOLITAIRE_H
