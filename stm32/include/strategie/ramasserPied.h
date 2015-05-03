#ifndef PIED_H
#define PIED_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class Pied : public MediumLevelAction
{
    public :
        Pied();
        Pied(Position position);
        ~Pied();
        int update();

    protected :
        Position position;
};

#endif // PIED_H
