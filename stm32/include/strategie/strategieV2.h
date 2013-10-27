#ifndef STRATEGIEV2_H_INCLUDED
#define STRATEGIEV2_H_INCLUDED

#include "command.h"
#include "ramasserVerreV2.h"
#include "mediumLevelAction.h"
#include "sharpSensor.h"
#include "ultrasoundSensor.h"
#ifndef ROBOTHW
#include "sensors.h"
#endif

class StrategieV2
{
    public:
        StrategieV2(bool blue = false);
        virtual ~StrategieV2();

        static void update();
        static void setCurrentGoal(Position goal, bool goBack, float maxSpeed = VITESSE_LINEAIRE_MAX);
        static void setCurrentGoal(Position goal, Position center, float vitesse, bool goBack);
        static void lookAt(Position pos);
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
        static void setCommand(Command* command);
        static bool sharpDetects(SharpSensor::SharpName name);
        static void setTourneSurSoiMeme(bool tourne);

#ifndef ROBOTHW
        static SharpSensor** getSensors();
#endif
        static bool somethingDetected;
        

    protected:
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
};

#endif // STRATEGIEV2_H_INCLUDED
