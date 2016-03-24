#ifndef CABINE_H
#define CABINE_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class Cabine : public MediumLevelAction
{
public:
    Cabine();

    Cabine(Position position, Position wd_position);

    ~Cabine();

    int update();

    Etape::EtapeType getType();

protected:
    Position position;
    Position position_depart;
};

#endif // CABINE_H
