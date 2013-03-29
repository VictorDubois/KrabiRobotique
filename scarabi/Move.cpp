#include "Move.h"

Move* Move::_singleton = 0;
Move* Move::singleton()
{
    if (_singleton==0)
        _singleton = new Move();
    return _singleton;
}

Move::Move()
{
    Serial.println("Move manager created !");

    inversedSense = false;

    sensorEnabled = true;
    performKind = MOVE_NONE;
    performStartTimer = 0;
    performTimeLeft = 0;
    performRunning = false;
    // Create the Servos
    wheelLeft = new Servo();
    wheelRight = new Servo();
    // Init the servos
    wheelLeft->attach(PIN_WL,210,2400);   //100,1500  || 200,2400
    wheelRight->attach(PIN_WR,230,2400);  //80,1500   || 220,2400
    // Init the sharp sensors
    initSharp();
    actionList = (MoveAction**) malloc(sizeof(MoveAction*) * ACTION_NUMBERS);
    actionNumber = 0;
    actionCurrent = 0;
    performSpeed = 0;
    performIsAccelerating = false;

    // Location
    x = 4.;
    y = 20.;
    angle = 0.;

    previousTime = micros();

    stop();
}

Move::~Move()
{
    //dtor
}

void Move::initSharp()
{
    sharpList = (Sharp**) malloc(sizeof(Sharp*) * SHARP_NUMBERS);
    sharpList[SHARP_FRONT_L] = new Sharp(A1);
    sharpList[SHARP_FRONT_R] = new Sharp(A3);
    sharpList[SHARP_FRONT_C] = new Sharp(A4);
    sharpList[SHARP_BEHIND] = new Sharp(A0);
}

void Move::updateSharp()
{
    for(int i(0); i<SHARP_NUMBERS; i++)
        sharpList[i]->update();
}

void Move::update(int timeSinceLastFrame)
{
    updateSharp();
    /*Serial.print("    Sharps (FL, FC, FL, B) : ");
            Serial.print(sharpList[SHARP_FRONT_L]->getValue());
            Serial.print(" ");
            Serial.print(sharpList[SHARP_FRONT_C]->getValue());
            Serial.print(" ");
            Serial.print(sharpList[SHARP_FRONT_R]->getValue());
            Serial.print(" ");
            Serial.print(analogRead(A1));
            Serial.print(" ");
            Serial.print(sharpList[SHARP_BEHIND]->getValue());
            Serial.print("\n");*/
    if (performKind!=MOVE_NONE)
    {
        if (placeFree(performKind) || performKind==DELAY || performKind==ENABLE_SHARPS || performKind==DISABLE_SHARPS)
        {
            if (!performRunning)
            {
                Serial.println("Robot no longer Detected, resume action");
                DiodeMgr::singleton()->getLed(2)->off();
                startAction(performKind);
            }
            doAction(performKind);

            // Timer update
            if (performIsAccelerating)
            {
                if (performSpeed<1.)
                    performSpeed += W_ACC;
                //if (performTimeLeft < WF_SPEED*performSpeed*W_INVACC)
                else
                    performIsAccelerating = false;
                //Serial.println(performSpeed);
            }
            else
            {
                /*if (performSpeed>0.4)
                    performSpeed -= W_ACC;
                else */if (performSpeed<0.3)
                    performSpeed = 0.3;
            }
            int factor = (micros() - previousTime)*performSpeed;
            previousTime = micros();
            //Serial.println(factor);

            performTimeLeft -= factor;
            switch(performKind)
            {
                case MOVE_45ANTICLOCK:
                    angle += factor/8334.;
                    break;
                case MOVE_45CLOCK:
                    angle -= factor/8334.;
                    break;
                default:
                    x += cos(angle) * factor / MOVE_TIME_DISTANCE_RATIO;
                    y += sin(angle) * factor / MOVE_TIME_DISTANCE_RATIO;
                    break;
            }

            if (performTimeLeft <= 0)
            {
                performIsAccelerating = false;
                Serial.print("    Finished ! position (x,y,angle) : (");
                Serial.print(x);
                Serial.print(" ");
                Serial.print(y);
                Serial.print(" ");
                Serial.print(angle);
                Serial.print(")\n");
                Serial.print("    Time spent over the limit : ");
                Serial.print(-performTimeLeft);
                Serial.print(" microseconds\n");
                stop();
                delay(150);
            }
        }
        else if (performRunning)
        {
            Serial.println("    Robot Detected, pause...");
            Serial.print("    Sharps (FL, FC, FL, B) : ");
            Serial.print(sharpList[SHARP_FRONT_L]->getValue());
            Serial.print(" ");
            Serial.print(sharpList[SHARP_FRONT_C]->getValue());
            Serial.print(" ");
            Serial.print(sharpList[SHARP_FRONT_R]->getValue());
            Serial.print(" ");
            Serial.print(sharpList[SHARP_BEHIND]->getValue());
            Serial.print("\n");
            DiodeMgr::singleton()->getLed(2)->on();
            pause();
            previousTime = micros();
        }
        else
            previousTime = micros();
    }
    else
    {
        // Treat the list
        if (actionNumber>actionCurrent)
        {
            DiodeMgr::singleton()->getLed(1)->on();
            perform(actionList[actionCurrent]->getKind(), actionList[actionCurrent]->getDistance());
            actionCurrent += 1;
        }
        else
            DiodeMgr::singleton()->getLed(1)->off();
        previousTime = micros();
    }
}

bool Move::perform(MOVE_KIND kind, float distance, bool overwrite)
{
    if (kind==MOVE_NONE)
    {
        stop();
        return true;
    }
    if (overwrite || isReady())
    {
        Serial.print("Starting action... ");
        performStartTimer = micros();
        switch(kind)
        {
            case DELAY:
                Serial.print("Delaying Skarabi");
                performTimeLeft = distance * 1000;
                break;
            case MOVE_45ANTICLOCK:
                Serial.print(45*distance);
                Serial.print(" degrees anti-clockwise");
                performTimeLeft = W_45ANTITIME * distance;
                break;
            case MOVE_45CLOCK:
                Serial.print(45*distance);
                Serial.print(" degrees clockwise");
                performTimeLeft = W_45CLOCKTIME * distance;
                break;
            case DISABLE_SHARPS:
                setSensor(false);
                Serial.print(" DISABLING SHARPS");
                performTimeLeft = 0;
                break;
            case ENABLE_SHARPS:
                setSensor(true);
                Serial.print(" ENABLING SHARPS");
                performTimeLeft = 0;
                break;
            default:
                performTimeLeft = distance * MOVE_TIME_DISTANCE_RATIO;
                break;
        }
        if (distance>0)
        {
            Serial.print(", duration : ");
            Serial.print(performTimeLeft/1000);
            Serial.print(" ms");
        }
        Serial.print("\n");

        startAction(kind);
        return true;
    }
    else
    {
        Serial.println("Can't start an action : the previous one wasn't finished !");
        return false;
    }
}

void Move::startAction(MOVE_KIND kind)
{
    performKind = kind;
    performRunning = true;
    performIsAccelerating = true;
    performSpeed = 1.;
    doAction(kind);
}

void Move::doAction(MOVE_KIND kind)
{
    switch(kind)
    {
        case MOVE_FORWARD:
            wheelLeft->write(WL_STOP + WL_FORWARD*WF_SPEED*performSpeed);
            wheelRight->write(WR_STOP + WR_FORWARD*WF_SPEED*performSpeed);
            break;
        case MOVE_BACKWARD:
            wheelLeft->write(WL_STOP + WL_BACKWARD*WF_SPEED*performSpeed);
            wheelRight->write(WR_STOP + WR_BACKWARD*WF_SPEED*performSpeed);
            break;
        case MOVE_45ANTICLOCK:
            wheelLeft->write(WL_STOP + WL_45ANTI*WF_SPEED*performSpeed);
            wheelRight->write(WR_STOP + WR_45ANTI*WF_SPEED*performSpeed);
            break;
        case MOVE_45CLOCK:
            wheelLeft->write(WL_STOP + WL_45CLOCK*WF_SPEED*performSpeed);
            wheelRight->write(WR_STOP + WR_45CLOCK*WF_SPEED*performSpeed);
            break;
    }
}

void Move::pause()
{
    performSpeed = 0;
    wheelLeft->write(WL_STOP);
    wheelRight->write(WR_STOP);
    performRunning = false;
}

void Move::stop()
{
    performSpeed = 0;
    Serial.println("Robot halted !");
    Serial.println("");
    wheelLeft->write(WL_STOP);
    wheelRight->write(WR_STOP);
    performKind = MOVE_NONE;
    performRunning = false;
}

bool Move::isReady()
{
    return (performKind == MOVE_NONE);
}

void Move::setSensor(bool enable)
{
    sensorEnabled = enable;
}

void Move::setInversedSense(bool inversed)
{
    inversedSense = inversed;
    Serial.println("Sense of rotation changed !");
}

bool Move::placeFree(MOVE_KIND kind)
{
    if (!sensorEnabled)
        return true;
    switch(kind)
    {
        case MOVE_FORWARD:
            return (!(sharpList[SHARP_FRONT_L]->getValue()||sharpList[SHARP_FRONT_R]->getValue()||sharpList[SHARP_FRONT_C]->getValue()));
            break;
        case MOVE_BACKWARD:
            return (!(sharpList[SHARP_BEHIND]->getValue()));
            break;
        case MOVE_45ANTICLOCK:
            return (!sharpList[SHARP_FRONT_L]->getValue());
            break;
        case MOVE_45CLOCK:
            return (!sharpList[SHARP_FRONT_R]->getValue());
            break;
        default:
            return false;
            break;
    }
}

void Move::addAction(MOVE_KIND kind, float distance)
{
    if (actionNumber < ACTION_NUMBERS-1)
    {
        Serial.println("Action added to the queue !");
        // Inverse if needed
        if (inversedSense)
        {
            if (kind==MOVE_45ANTICLOCK)
                kind = MOVE_45CLOCK;
            else if (kind==MOVE_45CLOCK)
                kind = MOVE_45ANTICLOCK;
        }
        actionList[actionNumber] = new MoveAction(kind,distance);
        actionNumber+=1;
    }
    else
        Serial.println("Can't queue action : too many actions !");
}
