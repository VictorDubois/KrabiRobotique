#include "actionnerPortes.h"

#define USE_DOORS_UPDATE_COUNT 50

ActionnerPortes::ActionnerPortes(bool close) : LowLevelAction(0)
{
    this->close = close;
#ifdef ROBOTHW
    this->servos[0] = NULL;
    this->servos[1] = NULL;
#endif
}
#ifdef ROBOTHW
ActionnerPortes::ActionnerPortes(Servo* servos[2], bool close) : LowLevelAction(0)
{
    this->close = close;
    this->servos[0] = servos[0];
    this->servos[1] = servos[1];
}
#endif
ActionnerPortes::~ActionnerPortes()
{
}
int ActionnerPortes::update() {
    if (status == 0)
        status = 1;
    //If action is ended, stop servos and return true.
    if (status > USE_DOORS_UPDATE_COUNT){
#ifdef ROBOTHW
        servos[0]->shutDownServo();
        servos[1]->shutDownServo();
#endif
        return 1;
    }
    //If first call : send order.
    if (status == 1){
        //If close is true, we close the doors. Else, we open them.
        if(close == true){
#ifdef ROBOTHW
            servos[0]->goToAngle(90);
            servos[1]->goToAngle(90);
#endif
        } else {
#ifdef ROBOTHW
            servos[0]->goToAngle(0);
            servos[1]->goToAngle(0);
#endif
        }
    }
    //Status is used as a count of calls to update
    status++;
    //Action not ended so return false.
    return 0;

}
