#include "KJ2016Tempo.h"

#include "interfaceServosNumeriques.h"
#include "actionneurs/fishingNet.h"

#include "clock.h"
#include "actionneurs/sensors.h"

KJ2016Tempo::KJ2016Tempo(unsigned int leftServoID, unsigned int rightServoID):
    LEFT_SERVO_ID(leftServoID), RIGHT_SERVO_ID(rightServoID), SERVO_SPEED_FACTOR((KJ2016Tempo::SERVO_MAX_RPM * 2*3.1415)/(1024*60))
{
    ServosNumeriques::changeContinuousRotationMode(LEFT_SERVO_ID,   true);
    ServosNumeriques::changeContinuousRotationMode(RIGHT_SERVO_ID,  true);
}


void KJ2016Tempo::run(bool isYellow)
{
    /** ID for the driving servos **/
    /* Left and right is relative to the starting position */
    const unsigned int SERVO_ONE_ID = 69;
    const unsigned int SERVO_TWO_ID = 15;

    KJ2016Tempo KJ(isYellow?SERVO_ONE_ID:SERVO_TWO_ID, isYellow?SERVO_TWO_ID:SERVO_ONE_ID);

    /** KJ Strategy **/
    KJ.move(750);       // Leave the start area
    KJ.turn90(true);    // First turn (now heading toward the tanks)
    KJ.move(1050);       // Drive into the wall
    KJ.move(-50);       // Back up for the turn
    KJ.turn90(false);   // Second turn (now parallel the tanks)
    KJ.move(200);       // Drive along the wall to the tanks

    FishingNet::getSingleton()->deploy();       // Deploy the arm
    FishingNet::getSingleton()->lowerNet();     // Deploy the net in the tank

    KJ.move(300);   // Drag the net in the tank

    FishingNet::getSingleton()->raiseNet(); // Raise the net
    FishingNet::getSingleton()->raiseArm(); // Raise the arm a little (to avoid the tank's sides

    KJ.move(100);   // Get to the target area

    FishingNet::getSingleton()->deploy();   // Lower the arm a bit
    FishingNet::getSingleton()->lowerNet(); // Lower the net

}


void KJ2016Tempo::stop()
{
    m_leftServoSpeed    = 0;
    m_rightServoSpeed   = 0;

    ServosNumeriques::moveAtSpeed(0, LEFT_SERVO_ID);
    ServosNumeriques::moveAtSpeed(0, RIGHT_SERVO_ID);
}

void KJ2016Tempo::pause()
{
    ServosNumeriques::moveAtSpeed(0, LEFT_SERVO_ID);
    ServosNumeriques::moveAtSpeed(0, RIGHT_SERVO_ID);
}

void KJ2016Tempo::resume()
{
    ServosNumeriques::moveAtSpeed(m_leftServoSpeed,     LEFT_SERVO_ID);
    ServosNumeriques::moveAtSpeed(m_rightServoSpeed,    RIGHT_SERVO_ID);
}

void KJ2016Tempo::turn90(bool toLeft)
{
    static const float alpha = (1000.f * KJ2016Tempo::KJ_INTERAXIS * 3.1415)/(KJ2016Tempo::SERVO_SPEED_FACTOR * KJ2016Tempo::KJ_WHEEL_DIAMETER * 2.f);

    unsigned int angularSpeed = 1023;

    m_leftServoSpeed    = (toLeft?0:1023) + angularSpeed;
    m_rightServoSpeed   = (toLeft?0:1023) + angularSpeed;

    resume();

    waitForArrival(static_cast<unsigned int>( alpha/(float)angularSpeed ));

    stop();
}

void KJ2016Tempo::move(int distance)
{
    static const float beta = (1000.f * 2.f)/(KJ2016Tempo::SERVO_SPEED_FACTOR * KJ2016Tempo::KJ_WHEEL_DIAMETER);

    unsigned int angularSpeed = 1023;

    m_leftServoSpeed    = (distance<0?1023:0) + angularSpeed;
    m_rightServoSpeed   = (distance>0?1023:0) + angularSpeed;

    resume();

    waitForArrival(static_cast<unsigned int>( beta * (float)((distance<0)?-distance:distance) / (float)angularSpeed ));
    stop();
}

void KJ2016Tempo::waitForArrival(unsigned int duration)
{
    unsigned int sensorCheckDelay = Clock::MS_PER_TICK * 10;

    while(true)
    {
        if(sensorCheckDelay > duration)
            sensorCheckDelay = duration;

        unsigned int t = Clock::delay(sensorCheckDelay);

        if(t >= duration)
            break;

        duration -= t;

        while(Sensors::getSingleton()->sharpDetect()) // We wait for all sharps to be clear
            pause();

        resume();
    }
}
