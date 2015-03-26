#ifndef STRATEGIEV2_H_INCLUDED
#define STRATEGIEV2_H_INCLUDED

#include "command.h"
#include "ramasserVerreV2.h"
#include "mediumLevelAction.h"
#include "sharpSensor.h"
#include "ultrasoundSensor.h"
#include "strategiev3.h"
//#include "canonFilet.h"

#ifndef ROBOTHW
#include "sensors.h"
#include <QPainter>
#else
#include "tourelle.h"
#endif

class StrategieV2
{
    public:
        StrategieV2(bool blue = false);
        virtual ~StrategieV2();

        static void update();
        static void setCurrentGoal(Position goal, bool goBack, float maxSpeed = VITESSE_LINEAIRE_MAX, Angle precisionAngle = -100.00);
        static void setCurrentGoal(Position goal, Position center, float vitesse, bool goBack, Angle precisionAngle = -100.00);
        static void lookAt(Position pos, float maxSpeed = VITESSE_ANGULAIRE_MAX);
        static void lookAt(Angle a, float maxSpeed = VITESSE_ANGULAIRE_MAX);
        static void addTemporaryAction(MediumLevelAction* action);
        static void gatherGlass();
        static void setJustAvoided(bool value);
        static bool getJustAvoided();
        static bool willCollide();
        static void setIsBlue(bool blue);
        static bool getIsBlue();
        static void emptySharpsToCheck();
        static void setEnTrainDeRecalibrer(bool recalibre);
        static void enableSharp(SharpSensor::SharpName name);
        static void enableSharpsGroup(bool front);
        static void setCommand(Command* command);
        static bool sharpDetects(SharpSensor::SharpName name);
        static void setTourneSurSoiMeme(bool tourne);
        static long getTimeSpent();
        static bool *getSharpsToCheck();

#ifndef ROBOTHW
        static SharpSensor** getSensors();

static void paint(QPainter* p);
#endif
        static bool somethingDetected;

    private:
        static bool isBlue;
        static int updateCount;
        static StrategieV2* strategie;
        static Command* currentCommand;
        static MediumLevelAction* currentAction;
        static MediumLevelAction* actionsToDo[32];
        static MediumLevelAction* delayedActions[10];
        static int numberOfActionsDelayed;
        static int actionsCount;
        static bool hasToGoBase;
        static bool mustDeleteAction;
        static int glassGathered;
        static int timeSinceLastRecalibration;
        static bool hasJustAvoided;
        static SharpSensor** sharps;
        static UltrasoundSensor* ultrasoundSensor;
        static Position positionsDeSecours[4];
        static int robotBloque;
        static bool enTrainDeRecalibrerOdometrie;
        static MediumLevelAction* evitement;
        static int timer;
        static bool sharpsToCheck[SharpSensor::END_SHARP_NAME];
        static bool tourneSurSoiMeme;
        static int timeToRestart;
        #ifdef ROBOTHW
            static Tourelle* tourelle;
            static int hysteresisTourelle;
        #endif
};

#endif // STRATEGIEV2_H_INCLUDED
