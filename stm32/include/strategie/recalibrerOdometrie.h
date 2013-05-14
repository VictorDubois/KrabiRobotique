#ifndef RECALIBRERODOMETRIE_H_INCLUDED
#define RECALIBRERODOMETRIE_H_INCLUDED

#include "mediumLevelAction.h"
#include "limitSwitchSensor.h"

class RecalibrerOdometrie : public MediumLevelAction
{
    public:
        RecalibrerOdometrie(bool isBlue = true);
        virtual ~RecalibrerOdometrie();

        virtual int update();
    protected:
    private:
        Position goalPosition1;
        Position goalPosition2;
        bool isBlue;
};

#endif // RECALIBRERODOMETRIE_H_INCLUDED
