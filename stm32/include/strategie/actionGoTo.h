#ifndef ACTIONGOTO_H_INCLUDED
#define ACTIONGOTO_H_INCLUDED

#include "mediumLevelAction.h"
#include "position.h"
//#include <stdint.h>


class ActionGoTo : public MediumLevelAction
{
    public:
        ActionGoTo(Position goalPos = Position(0,0), bool goBack1 = false, float _precision = 30.f);
        virtual ~ActionGoTo();

        virtual int update();
        virtual void collisionAvoided();
        void reset();
    protected:
    private:
        float goalAngle;
        bool goingCurve;
        int curveFactor;
        float precision;
        Position intermediateGoalPosition;
};

#endif // ACTIONGOTO_H_INCLUDED
