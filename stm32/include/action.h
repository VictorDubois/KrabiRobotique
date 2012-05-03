#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

#include "PositionPlusAngle.h"
#include "odometrie.h"
#include "CommandGoTo.h"
#include "variable.h"

class Action {
    public:
        Action() {}
        virtual ~Action() {}
        virtual bool executer() = 0; // renvoit vrai si l'action est terminee
};

class ActionBase
{
    public:
    ActionBase();

    Position position;
    bool reculer;
};

#endif
