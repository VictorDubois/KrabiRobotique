#ifndef MOVEACTION_H
#define MOVEACTION_H

#include <Arduino.h>
#include "Constante.h"

class Move;
class MoveAction
{
    public:
        MoveAction(MOVE_KIND kind, float distance = 0.);
        virtual ~MoveAction();

        MOVE_KIND getKind();
        float getDistance();
    protected:
    private:
        MOVE_KIND action_kind;
        float action_distance;
};

#endif // MOVEACTION_H
