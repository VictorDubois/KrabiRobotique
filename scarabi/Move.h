#ifndef MOVE_H
#define MOVE_H

#include <Arduino.h>
#include <Servo.h>
#include "Sharp.h"
#include "MoveAction.h"
#include "Constante.h"
#include "DiodeMgr.h"

#define WF_SPEED                    1.5
#define W_ACC                       0.000001
#define W_INVACC                    1000000

#define PIN_WL                      5
#define PIN_WR                      3

#define WL_STOP                     90
#define WR_STOP                     90

#define WL_FORWARD                  11.5
#define WR_FORWARD                  -11.5

#define WL_BACKWARD                 -10
#define WR_BACKWARD                 40

#define WL_45ANTI                   -10
#define WR_45ANTI                   -10
#define W_45ANTITIME                380000

#define WL_45CLOCK                  40
#define WR_45CLOCK                  40
#define W_45CLOCKTIME               380000

#define MOVE_TIME_DISTANCE_RATIO    45000

#define SHARP_NUMBERS               4
#define ACTION_NUMBERS              50

class Move
{
    public:
        static Move* singleton();
        void update(int timeSinceLastFrame);

        void addAction(MOVE_KIND kind, float distance = 1);
        bool perform(MOVE_KIND kind, float distance = 0, bool overwrite = false);
        void stop();
        void pause();

        bool placeFree(MOVE_KIND kind);

        void setInversedSense(bool inversed);

        bool isReady();
        void setSensor(bool enable);

        void startAction(MOVE_KIND kind);
    protected:
    private:
        static Move* _singleton;
        Move();
        virtual ~Move();

        Servo *wheelLeft, *wheelRight;
        MOVE_KIND performKind;
        int actionNumber, actionCurrent;
        float performSpeed;
        bool performRunning, sensorEnabled, performIsAccelerating;
        Sharp** sharpList;
        MoveAction** actionList;

        void initSharp();
        void updateSharp();

        bool inversedSense;

        long previousTime, performStartTimer, performTimeLeft;
        float x, y, angle;

        void doAction(MOVE_KIND kind);
};

#endif // MOVE_H
