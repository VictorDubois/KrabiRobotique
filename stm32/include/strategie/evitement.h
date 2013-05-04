#ifndef EVITEMENT_H
#define EVITEMENT_H

#include "mediumLevelAction.h"
#include "odometrie.h"

class Evitement : public MediumLevelAction
{
    public:
        Evitement();
        virtual ~Evitement();

    protected:
        virtual int update();

};

#endif // EVITEMENT_H
