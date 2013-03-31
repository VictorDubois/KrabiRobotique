#include "MoveAction.h"
#include "Move.h"

MoveAction::MoveAction(MOVE_KIND kind, float distance) : action_kind(kind), action_distance(distance)
{

}

MoveAction::~MoveAction()
{

}

MOVE_KIND MoveAction::getKind()
{
    return action_kind;
}

float MoveAction::getDistance()
{
    return action_distance;
}
