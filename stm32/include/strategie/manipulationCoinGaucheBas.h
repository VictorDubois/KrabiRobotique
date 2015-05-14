#ifndef MANIPULATION_COIN_GAUCHE_BAS_H
#define MANIPULATION_COIN_GAUCHE_BAS_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class ManipulationCoinGaucheBas : public MediumLevelAction
{
    public :
        ManipulationCoinGaucheBas(Position positionDepart, bool isYellow);
        ~ManipulationCoinGaucheBas();
        int update();
        Etape::EtapeType getType();

    private :
        bool isYellow;
};

#endif // MANIPULATION_COIN_GAUCHE_BAS_H
