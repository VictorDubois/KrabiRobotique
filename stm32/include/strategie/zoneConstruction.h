#ifndef ZONECONSTRUCTION_H
#define ZONECONSTRUCTION_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class ZoneConstruction : public MediumLevelAction
{
public:
    ZoneConstruction();

    ZoneConstruction(Position goalPosition);

    ~ZoneConstruction();

    int update();

    Etape::EtapeType getType();

protected:
    Position goalPosition;
};

#endif // ZONECONSTRUCTION_H
