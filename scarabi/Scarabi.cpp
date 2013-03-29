#include "Scarabi.h"

Scarabi* Scarabi::_singleton = 0;
Scarabi* Scarabi::singleton()
{
    if (_singleton==0)
        _singleton = new Scarabi();
    return _singleton;
}

Scarabi::Scarabi() : color(colorBlue), timerMatchStarted(0), isRunning(false)
{
    Serial.println("Skarabi created !");
    Serial.println("First it was Scarabi, but now it's Skarabi...");

    Move::singleton();

    pinMode(PIN_TIRETTE, INPUT);

    matchTimeInfo = TIME_INFO;
}

Scarabi::~Scarabi()
{
    //dtor
}

void Scarabi::update()
{
    // Call in the loop function
    currentTimer = micros();
    if (isRunning)
    {
        if (currentTimer - timerMatchStarted >= TIME_MATCH - 1000000)
        {
            isRunning = false;
            Move::singleton()->stop();
            Serial.print("END OF THE MATCH !!!");
        }
        else
        {
            Move::singleton()->update(micros() - previousTimer);
            if (currentTimer - timerMatchStarted >= matchTimeInfo - 1000)
            {
                Serial.print((TIME_MATCH - currentTimer + timerMatchStarted)/1000000);
                Serial.print(" seconds left until the end of the match !\n");
                matchTimeInfo += TIME_INFO;
            }
        }
    }
    previousTimer = micros();
}

void Scarabi::waitTirette(bool avoid)
{
    Serial.println("Waiting for the tirette to be removed...");
    // Waits for the tirette to be removed
    bool tiretteWasPresent = false;
    if (!avoid)
        while(true)
        {
            if (digitalRead(PIN_TIRETTE)==LOW && tiretteWasPresent)
                break;
            if (digitalRead(PIN_TIRETTE)==HIGH)
                tiretteWasPresent = true;
        }
    Serial.println("Tirette removed !");
    // Beginning of the match timer
    timerMatchStarted = micros();
    isRunning = true;
    // Departure area
    if(digitalRead(PIN_COLOR)==HIGH)
        color = colorBlue;
    else
        color = colorRed;
    // Debug
    //Move::singleton()->startAction(MOVE_FORWARD);
}

Scarabi::sideColor Scarabi::getColor()
{
    return color;
}

void Scarabi::finalStop()
{
    isRunning = false;
}
