#ifndef DEPOSERPIED_H
#define DEPOSERPIED_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class DeposerPied : public MediumLevelAction
{
public:
    DeposerPied();
    DeposerPied(Position position, bool isYellow);
    ~DeposerPied();
    Etape::EtapeType getType();
    int update();

private :
    Position positionRetournement;
};


#endif // DEPOSERPIED_H
