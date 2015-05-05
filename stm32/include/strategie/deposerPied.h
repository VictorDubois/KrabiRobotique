#ifndef DEPOSERPIED_H
#define DEPOSERPIED_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class DeposerPied : public MediumLevelAction
{
public:
    DeposerPied();
    DeposerPied(Position position);
    ~DeposerPied();
    int update();

protected :
    Position position;
};


#endif // DEPOSERPIED_H
