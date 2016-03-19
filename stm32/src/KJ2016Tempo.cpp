#include "KJ2016Tempo.h"

#include "interfaceServosNumeriques.h"
#include "actionneurs/fishingNet.h"

#include "clock.h"

KJ2016Tempo::KJ2016Tempo(unsigned int leftServoID, unsigned int rightServoID): LEFT_SERVO_ID(leftServoID), RIGHT_SERVO_ID(rightServoID)
{}

KJ2016Tempo::~KJ2016Tempo()
{
    enginesStop();
}


void KJ2016Tempo::run(bool isYellow)
{
    /** ID for the driving servos **/
    /* Left and right is relative to the starting position */
    const unsigned int SERVO_ONE_ID = 0;
    const unsigned int SERVO_TWO_ID = 1;

    KJ2016Tempo KJ(isYellow?SERVO_ONE_ID:SERVO_TWO_ID, isYellow?SERVO_TWO_ID:SERVO_ONE_ID);

    /** KJ Strategy **/
    KJ.move(100);       // Leave the start area
    KJ.turn90(true);    // First turn (now heading toward the tanks)
    KJ.move(500);       // Drive into the wall
    KJ.move(-50);       // Back up for the turn
    KJ.turn90(false);   // Second turn (now parallel the tanks)
    KJ.move(200);       // Drive along the wall to the tanks

    FishingNet::getSingleton()->deploy();       // Deploy the arm
    FishingNet::getSingleton()->lowerNet();     // Deploy the net in the tank

    KJ.move(100);   // Drag the net in the tank

    FishingNet::getSingleton()->raiseNet(); // Raise the net
    FishingNet::getSingleton()->raiseArm(); // Raise the arm a little (to avoid the tank's sides

    KJ.move(100);   // Get to the target area

    FishingNet::getSingleton()->deploy();   // Lower the arm a bit
    FishingNet::getSingleton()->lowerNet(); // Lower the net

}

void KJ2016Tempo::enginesStart()
{
    ServosNumeriques::changeContinuousRotationMode(LEFT_SERVO_ID,   true);
    ServosNumeriques::changeContinuousRotationMode(RIGHT_SERVO_ID,  true);
}

void KJ2016Tempo::enginesStop()
{
    ServosNumeriques::changeContinuousRotationMode(LEFT_SERVO_ID,   false);
    ServosNumeriques::changeContinuousRotationMode(RIGHT_SERVO_ID,  false);
}

void KJ2016Tempo::turn90(bool toLeft)
{
    const float correctionFactor = 1.0f;

    const unsigned int servoOne = toLeft?LEFT_SERVO_ID:RIGHT_SERVO_ID;
    const unsigned int servoTwo = toLeft?RIGHT_SERVO_ID:LEFT_SERVO_ID;

    const unsigned int speed = 0x0100;

    enginesStart();

    ServosNumeriques::moveAtSpeed(0x0400 - speed, servoOne);
    ServosNumeriques::moveAtSpeed(0x0400 + speed, servoTwo);

    Clock::delay(static_cast<unsigned int>( 1/((float)speed) * correctionFactor));

    enginesStop();
}

void KJ2016Tempo::move(int distance)
{
    const float correctionFactor = 1.f;

    unsigned int speed = 0x0100;

    speed = (distance>0)?speed:-speed;

    enginesStart();

    ServosNumeriques::moveAtSpeed(0x0400 + speed, LEFT_SERVO_ID);
    ServosNumeriques::moveAtSpeed(0x0400 + speed, RIGHT_SERVO_ID);

    Clock::delay(static_cast<unsigned int>((float)distance / (float)speed * correctionFactor));
    enginesStop();
}
