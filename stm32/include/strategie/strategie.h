#ifndef STRATEGIE_H_INCLUDED
#define STRATEGIE_H_INCLUDED

#include "singleton.h"

class Strategie: public Singleton<Strategie> {
    friend class Singleton<Strategie>;
private:
    Sensors* sensors;
	int goalPosition[2];
	bool mustMove;
	/**
	 * Intermediate positions to reach the goal, if any. This is use to avoid colliding other robots or being blocked
	 */
	std::vector<int> intermediatePositions;
	/**
	 * Vector that stores all the actions that can be performed during a match
	 */
	MediumLevelAction* actions[32];
	/**
	 * Ordered list of pointers on all the actions that must be done
	 */
	std::vector<MediumLevelAction*> actionsToDo;
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

public:
    Strategie();
    virtual ~Strategie();
    /**
     * Setups the strategy, intiates all the actions and the base actionsToDoVector
     */
    void setup();
	bool update();

	void goToTarget();

	int getLastRobotDetection();

	bool getMustMove();

	void setMustMove(bool mustMove);
};

#endif
