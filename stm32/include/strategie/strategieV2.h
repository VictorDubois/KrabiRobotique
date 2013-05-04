#ifndef STRATEGIEV2_H_INCLUDED
#define STRATEGIEV2_H_INCLUDED

#include "command.h"
#include "ramasserVerreV2.h"
#include "mediumLevelAction.h"

class StrategieV2
{
    public:
        StrategieV2();
        virtual ~StrategieV2();

        static void update();
        static void setCurrentGoal(Position goal, bool goBack);
        static void setCurrentGoal(Position goal, Position center, float vitesse, bool goBack);
        static void lookAt(Position pos);
        static void addTemporaryAction(MediumLevelAction* action);
        static void gatherGlass();
        static void setJustAvoided(bool value);
        static bool getJustAvoided();
        static bool willCollide();

        static bool somethingDetected;

    protected:
    private:
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
};

#endif // STRATEGIEV2_H_INCLUDED
