#ifndef RECALIBRERODOMETRIE_H_INCLUDED
#define RECALIBRERODOMETRIE_H_INCLUDED

#include "mediumLevelAction.h"

class RecalibrerOdometrie : public MediumLevelAction
{
    public:
        RecalibrerOdometrie();
        virtual ~RecalibrerOdometrie();

        virtual int update();
    protected:
    private:
        Position goalPosition1;
        Position goalPosition2;
};

#endif // RECALIBRERODOMETRIE_H_INCLUDED
