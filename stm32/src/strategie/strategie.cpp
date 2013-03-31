#include "strategie.h"

Strategie::Strategie(bool isBlue, Odometrie* odometrie)
{
    this->isBlue = isBlue;
    this->odometrie = odometrie;
    this->updateCallsCount = 0;
    this->mustMove = false;
}
Strategie::~Strategie()
{

}

void Strategie::setup() {
    actions[] =
}

bool Strategie::update() {
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
