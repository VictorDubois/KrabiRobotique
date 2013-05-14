#ifndef RAMASSERVERRES_H
#define RAMASSERVERRES_H

#include "actionGoTo.h"
#include "mediumLevelAction.h"

class RamasserVerres : public MediumLevelAction
{
    public:
        RamasserVerres();
        virtual ~RamasserVerres();

        virtual int update();
        
        void othersTurn();
    protected:
    private:
        ActionGoTo positionsToGo[6][7];
        bool demiLignesRamassees[6][2];
        int ligneEnCours;
        bool ramasserTouteLaLigne;
        int nextPosition;
        Position nextGoalPos;
        bool myTurn;
        
};

#endif // RAMASSERVERRES_H
