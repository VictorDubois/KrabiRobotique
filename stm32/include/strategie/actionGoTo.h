#ifndef ACTIONGOTO_H_INCLUDED
#define ACTIONGOTO_H_INCLUDED

#include "mediumLevelAction.h"

class ActionGoTo : public MediumLevelAction
{
    public:
        ActionGoTo(Position goalPos = Position(0,0), bool goBack1 = false);
        virtual ~ActionGoTo();

        virtual int update();
        virtual void collisionAvoided();
    protected:
    private:
        float goalAngle;
        bool goingCurve;
        int curveFactor;
};

#endif // ACTIONGOTO_H_INCLUDED
