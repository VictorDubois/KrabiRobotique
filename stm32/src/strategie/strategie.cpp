#include "strategie.h"

bool Strategie::setup() {
	
}

bool Strategie::update() {
	throw "Not yet implemented";
}

void Strategie::goToTarget() {
	PositionPlusAngle pos_plus_angle = Odometrie::getPos();
    Position pos = pos_plus_angle.getPosition();
    Angle angle = pos_plus_angle.getAngle();

    
	SharpNameVector* sharpsDatDetect = sensors->detectedSharp();
    if (sharpsDatDetect->size() > 0) // have to find a new path
    {
        
    }
    
    return true;
}

int Strategie::getLastRobotDetection() {
	return this->lastRobotDetection;
}

bool Strategie::getMustMove() {
	return this->mustMove;
}

void Strategie::setMustMove(bool mustMove) {
	this->mustMove = mustMove;
}
