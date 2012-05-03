#ifndef ACTIONCHERCHERPIECE_H_INCLUDED

#define ACTIONCHERCHERPIECE_H_INCLUDED

#include "PositionPlusAngle.h"
#include "odometrie.h"
#include "CommandGoTo.h"
#include "action.h"

class ActionChercherPiece : public Action
{
    private:
    Position destinationFinale;
    Odometrie* odometrie;
    CommandGoTo* commandActuelle;
    Position positionIntermediaire;
    int nbPositionIntermediaire;
    int numeroPositionSuivante;
    Position positionIntermediaireUn;
    Position positionIntermediaireDeux;

    public:

    ActionChercherPiece(Position destinationFinale, Odometrie* odometrie, bool is_Blue);
    virtual ~ActionChercherPiece();
    virtual bool executer();
};

#endif
