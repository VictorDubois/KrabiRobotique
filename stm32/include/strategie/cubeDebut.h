#ifndef CUBEDEBUT_H
#define CUBEDEBUT_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class CubeDebut : public MediumLevelAction
{
public:
    CubeDebut();

    CubeDebut(Position position);

    ~CubeDebut();

    int update();

    Etape::EtapeType getType();

protected:
    Position position;
};

#endif // CUBEDEBUT_H
