#ifndef DEPOSERVERRES_H_INCLUDED
#define DEPOSERVERRES_H_INCLUDED

#include "mediumLevelAction.h"

class DeposerVerres : public MediumLevelAction {

public:
    DeposerVerres(Position position = Position(-1,-1));
    virtual ~DeposerVerres();

    virtual int update();
};

#endif // DEPOSERVERRES_H_INCLUDED

