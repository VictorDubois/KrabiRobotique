#ifndef MANIPULATION_COIN_GAUCHE_HAUT_H
#define MANIPULATION_COIN_GAUCHE_HAUT_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class ManipulationCoinGaucheHaut : public MediumLevelAction
{
    public :
        ManipulationCoinGaucheHaut(Position positionDepart, bool isYellow);
        ~ManipulationCoinGaucheHaut();
        int update();
        Etape::EtapeType getType();

    private :
        bool isYellow;
};

#endif // MANIPULATION_COIN_GAUCHE_HAUT_H
