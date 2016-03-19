#ifndef ZONECONSTRUCTION_H
#define ZONECONSTRUCTION_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "benne.h"

class ZoneConstruction : public MediumLevelAction
{
public:
    ZoneConstruction();

    ZoneConstruction(Position goalPosition, Benne* benne);

    ~ZoneConstruction();

    int update();

    Etape::EtapeType getType();

protected:
    Position goalPosition;
    Benne* benne_locale;
};

#endif // ZONECONSTRUCTION_H
