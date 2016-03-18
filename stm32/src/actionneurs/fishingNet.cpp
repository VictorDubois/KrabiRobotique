#include "fishingNet.h"

#ifdef ROBOTHW
    #include "interfaceServosNumeriques.h"
#endif

FishingNet* FishingNet::getSingleton()
{
    static FishingNet* instance = 0;
    if(instance == 0)
        instance = new FishingNet();

    return instance;
}

FishingNet::FishingNet()
{
    close();
}

void FishingNet::moveArm(int __attribute__((__unused__)) destAngle)
{
#ifdef ROBOTHW
    ServosNumeriques::moveTo(destAngle, SERVO_EXT_ID);
#endif
}

void FishingNet::rotateArm(int __attribute__((__unused__)) destAngle)
{
#ifdef ROBOTHW
    ServosNumeriques::moveTo(destAngle, SERVO_INT_ID);
#endif
}

void FishingNet::close()
{
    rotateArm(SERVO_INT_RAISED_POS);
    moveArm(SERVO_EXT_CLOSED_POS);
}

void FishingNet::deploy()
{
    moveArm(SERVO_EXT_DEPLOYED_POS);
    rotateArm(SERVO_INT_RAISED_POS);
}

void FishingNet::lowerNet()
{
    rotateArm(SERVO_INT_LOWERED_POS);
}

void FishingNet::raiseNet()
{
    rotateArm(SERVO_INT_RAISED_POS);
}

void FishingNet::raiseArm()
{
    moveArm(SERVO_EXT_RAISED_POS);
}
