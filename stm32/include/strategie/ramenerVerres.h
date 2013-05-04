#ifndef RAMENERVERRES_H_INCLUDED
#define RAMENERVERRES_H_INCLUDED

#include "mediumLevelAction.h"

class RamenerVerres : public MediumLevelAction
{
    public:
        RamenerVerres(Position goalPos = Position(0,0));
        virtual ~RamenerVerres();

        virtual int update();
    protected:
    private:
};

#endif // RAMENERVERRES_H_INCLUDED
