#ifndef DEPOSERGOBELET_H
#define DEPOSERGOBELET_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"

class DeposerGobelet : public MediumLevelAction
{
public:
    DeposerGobelet();
    DeposerGobelet(Position position);
    ~DeposerGobelet();
    int update();

protected :
    Position position;
};

#endif // DEPOSERGOBELET_H
