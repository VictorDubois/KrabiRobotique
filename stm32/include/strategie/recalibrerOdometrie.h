#ifndef RECALIBRERODOMETRIE_H_INCLUDED
#define RECALIBRERODOMETRIE_H_INCLUDED

#include "mediumLevelAction.h"
#include "limitSwitchSensor.h"

class RecalibrerOdometrie : public MediumLevelAction
{
    public:
        RecalibrerOdometrie(LimitSwitchSensor* _fdc1, LimitSwitchSensor* _fdc2);
        virtual ~RecalibrerOdometrie();

        virtual int update();
    protected:
    private:
        Position goalPosition1;
        Position goalPosition2;
        LimitSwitchSensor* fdc1;
        LimitSwitchSensor* fdc2;
};

#endif // RECALIBRERODOMETRIE_H_INCLUDED
