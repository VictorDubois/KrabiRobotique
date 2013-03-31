#include "strategie.h"
#include "asservissement.h"


Strategie::Strategie(bool isBlue, Odometrie* odometrie)
{
    this->isBlue = isBlue;
    this->odometrie = odometrie;
    this->updateCallsCount = 0;
    this->mustMove = false;
    this->currentCommand = CommandGoTo(Position(0,0));
    this->i = 0;
}
Strategie::~Strategie()
{

}

void Strategie::setup() {
    // verres :
    actions[0] = RamasserVerre(Position(900,550));
    actions[1] = RamasserVerre(Position(900,1050));
    actions[2] = RamasserVerre(Position(1050,800));
    actions[3] = RamasserVerre(Position(1200,550));
    actions[4] = RamasserVerre(Position(1200,1050));
    actions[5] = RamasserVerre(Position(1350,800));
    actions[6] = RamasserVerre(Position(2100,550));
    actions[7] = RamasserVerre(Position(2100,1050));
    actions[8] = RamasserVerre(Position(1950,800));
    actions[9] = RamasserVerre(Position(1800,550));
    actions[10] = RamasserVerre(Position(1800,1050));
    actions[11] = RamasserVerre(Position(1650,800));
    actions[12] = RamasserVerre(Position(200,1400));
    actions[13] = RamasserVerre(Position(200,500));

    //actions[] = RamasserVerre(Position(,));

    actionsToDo[0] = &actions[0];
    actionsToDo[1] = &actions[2];
    actionsToDo[2] = &actions[1];
    actionsToDo[3] = &actions[12];
    actionsToDo[4] = &actions[3];
    actionsToDo[5] = &actions[4];
    actionsToDo[6] = &actions[5];
    actionsToDo[7] = &actions[6];
    actionsToDo[8] = &actions[7];
    actionsToDo[9] = &actions[8];
    actionsToDo[10] = &actions[9];
    actionsToDo[11] = &actions[10];
    actionsToDo[12] = &actions[11];

    MediumLevelAction* action = actionsToDo[0];
    currentCommand = CommandGoTo(action->getRobotPosition());
    Asservissement::asservissement->setCommand(&currentCommand);
}

bool Strategie::update() {

    float distance = (actionsToDo[i]->getRobotPosition() - odometrie->getPos().getPosition()).getNorme();
    if (distance < 10)
    {
        i++;
        currentCommand = CommandGoTo(actionsToDo[i]->getRobotPosition());
        Asservissement::asservissement->setCommand(&currentCommand);
    }
    return true;
}

void Strategie::goToTarget() {
	PositionPlusAngle pos_plus_angle = odometrie->getPos();
    Position pos = pos_plus_angle.getPosition();
    Angle angle = pos_plus_angle.getAngle();



	Sensors::SharpNameVector* sharpsDatDetect = sensors->detectedSharp();
    if (sharpsDatDetect->getSize() > 0) // have to find a new path
    {

    }


}

int Strategie::getLastRobotDetection() {
	return this->lastRobotDetection;
}

bool Strategie::getMustMove() {
	return this->mustMove;
}

bool Strategie::getIsBlue() {
	return this->isBlue;
}

void Strategie::setMustMove(bool mustMove) {
	this->mustMove = mustMove;
}
void Strategie::setIsBlue(bool isBlue) {
	this->isBlue = isBlue;
}
void Strategie::setOdometrie(Odometrie* odometrie)
{
    this->odometrie = odometrie;
}
