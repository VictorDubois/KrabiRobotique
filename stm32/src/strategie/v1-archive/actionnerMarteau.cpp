#include "actionnerMarteau.h"


#ifdef ROBOTHW
#include "interfaceServosNumeriques.h"
#else
#include "table.h"
#endif

ActionnerMarteau::ActionnerMarteau(int AX12ID, int goalAngle, int speed) : LowLevelAction(0)
{
    this->AX12ID = AX12ID;
    this->goalAngle = goalAngle;
    this->speed = speed;
}
ActionnerMarteau::~ActionnerMarteau()
{
}
int ActionnerMarteau::update()
{
    if (status == 0)
        status = 1;

    if (status == 1)
    {
#ifdef ROBOTHW
        ServosNumeriques::moveToAtSpeed(goalAngle, speed, AX12ID);
#else
        Table::getInstance()->getMainRobot()->startLeftLowerHammer();
#endif
        status = -1;
    }
    return status;
}
