#ifndef DUNE_H
#define DUNE_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "benne.h"

class Dune : public MediumLevelAction
{
public:
    Dune();

    Dune(Position position, Benne* benne);

    ~Dune();

    int update();

    Etape::EtapeType getType();

protected:
    Position position;
    Benne* benne_locale;
};

#endif // DUNE_H
