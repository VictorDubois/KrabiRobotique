#ifndef PIED_H
#define PIED_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class RamasserPied : public MediumLevelAction
{
    public :
        RamasserPied();
        RamasserPied(Position position);
        ~RamasserPied();
        int update();
        Etape::EtapeType getType();

    protected :
        Position position;
        bool coin;
};

#endif // PIED_H
