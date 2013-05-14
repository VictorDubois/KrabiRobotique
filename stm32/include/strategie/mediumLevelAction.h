#ifndef MEDIUMLEVELACTION_H_INCLUDED
#define MEDIUMLEVELACTION_H_INCLUDED

#include "position.h"

class MediumLevelAction
{
    public:
        MediumLevelAction(Position goalPos = Position(0,0));
        virtual ~MediumLevelAction();

        virtual int     update() = 0;
        virtual bool    getGoBack();
        virtual void    collisionAvoided();
        void            setGoBack(bool val);

        Position getGoalPosition();
    protected:
        Position goalPosition;
        int status;
        bool goBack;
    private:
};

#endif // MEDIUMLEVELACTION_H_INCLUDED
