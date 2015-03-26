#ifndef RAMASSERVERREV2_H_INCLUDED
#define RAMASSERVERREV2_H_INCLUDED

#include "position.h"
#include "mediumLevelAction.h"

class RamasserVerreV2 : public MediumLevelAction
{
    public:
        RamasserVerreV2(Position goalPos = Position(270,550));
        virtual ~RamasserVerreV2();

        virtual int update();

    protected:
    private:
};

#endif // RAMASSERVERREV2_H_INCLUDED
