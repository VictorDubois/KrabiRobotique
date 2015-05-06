#ifndef GOBELET_H
#define GOBELET_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class Gobelet : public MediumLevelAction
{
    public :
        Gobelet();
        Gobelet(Position position);
        ~Gobelet();
        int update();
        Etape::EtapeType getType();

    protected :
        Position position;
};

#endif // GOBELET_H
