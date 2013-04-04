#ifndef STRATEGIE_H_INCLUDED
#define STRATEGIE_H_INCLUDED

#include "singleton.h"
#ifdef ROBOTHW
#include "vector.h"
#else
#include <vector>
#endif
#include "mediumLevelAction.h"
#include "sensors.h"
#include "odometrie.h"
#include "positionPlusAngle.h"
#include "position.h"
#include "angle.h"
#include "sharpSensor.h"
#include "commandGoTo.h"
#include "commandLookAt.h"
#include "asservissement.h"
#include "leds.h"

#define DISTANCE_TO_CATCH_GLASS 150

class Strategie: public Singleton<Strategie> {
    friend class Singleton<Strategie>;

public:
    Strategie(bool isBlue = true);
    virtual ~Strategie();
    /**
     * Setups the strategy, intiates all the actions and the base actionsToDoVector
     */
    void setup(bool isBlue = true);
	bool update();

	void goToTarget();

	int getLastRobotDetection();

	bool getMustMove();
	bool getIsBlue();
    Odometrie* getOdometrie();

	void setMustMove(bool mustMove);
	void setIsBlue(bool isBlue);
    void updateGoal(Position goalPos, bool goBack = false);
    void storeGlass(); // function to tell the strategy we have an other glass
    void cleanGlassStorage();
    bool hasBeenSetUp();

private:
    Sensors* sensors;
	Position goalPosition;
	Angle goalAngle;
	bool mustMove;
    bool isBlue;
    int i;
    int updateCallsCount; /// Contains the number of update function calls
    bool hasToldBack;
    int numberOfGlassStored;
    bool mustComeToBase;
    MediumLevelAction* currentAction;
    bool setUp;
    Command* currentCommand;
	/**
	 * Intermediate positions to reach the goal, if any. This is use to avoid colliding other robots or being blocked
	 */
	vector<int> intermediatePositions;
	/**
	 * Vector that stores all the actions that can be performed during a match
	 */
    MediumLevelAction* actions[32];
	/**
	 * Ordered list of pointers on all the actions that must be done
     */
    MediumLevelAction* actionsToDo[12];
	/**
	 * set to 0 each time a robot has been seen
	 * increased by dt each time update is called
	 */
	int lastRobotDetection;
	/**
	 * If we're doing an action that can be continued while doing another, the action to be finished is stored here
	 */
	MediumLevelAction* actionToFinish;
	/**
	 * Contains the positions of detected robots on the table, if any. (-1,-1) means we don't know where other robots are.
	 */
	int otherRobotsPosition[3][2];

};

#endif
