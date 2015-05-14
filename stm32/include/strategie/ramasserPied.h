#ifndef PIED_H
#define PIED_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class RamasserPied : public MediumLevelAction
{
    public :
        RamasserPied();
        RamasserPied(Position goalPosition, bool recule = false);
        ~RamasserPied();
        int update();
        Etape::EtapeType getType();

    protected :
        Position depart;
        bool recule;
};

#endif // PIED_H
