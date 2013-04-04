#include "strategie.h"
#include "asservissement.h"
#include "ramasserVerre.h"
#include "eteindreBougie.h"
#include "actionnerAscenseur.h"
#include "actionnerMarteau.h"
#include "actionnerPortes.h"
#include "lancerAscenseur.h"
#include "regarderCouleur.h"
#include "deposerVerres.h"
#ifndef ROBOTHW
#include "table.h"
#endif


Strategie::Strategie(bool isBlue)
{
    this->isBlue = isBlue;
    this->updateCallsCount = 0;
    this->mustMove = false;
    this->currentCommand = NULL;
    this->i = 0;
    this->numberOfGlassStored = 0;
    this->mustComeToBase = false;
    this->setUp = false;
}
Strategie::~Strategie()
{

}

void Strategie::setup(bool isBlue)
{
    this->isBlue = isBlue;

    // verres :


/*
    // bougies bas
    actions[12] = new EteindreBougie(Position(826,1910), 0, 1);
    actions[13] = new EteindreBougie(Position(872,1740), 0);
    actions[14] = new EteindreBougie(Position(961,1586), 0);
    actions[15] = new EteindreBougie(Position(1086,1461), 0, 1);
    actions[16] = new EteindreBougie(Position(1240,1372), 0, 1);
    actions[17] = new EteindreBougie(Position(1411,1326), 0, 1);
    actions[18] = new EteindreBougie(Position(1589,1326), 0, 1);
    actions[19] = new EteindreBougie(Position(1760,1372), 0, 1);
    actions[20] = new EteindreBougie(Position(1914,1461), 0);
    actions[21] = new EteindreBougie(Position(2039,1586), 0, 1);
    actions[22] = new EteindreBougie(Position(2128,1740), 0, 1);
    actions[23] = new EteindreBougie(Position(2174,1910), 0);

    // bougies haut
    actions[24] = new EteindreBougie(Position(833,1910), 0, 1);
    actions[25] = new EteindreBougie(Position(935,1722), 0);
    actions[26] = new EteindreBougie(Position(1122,1535), 0, 1);
    actions[27] = new EteindreBougie(Position(1367,1433), 0);
    actions[28] = new EteindreBougie(Position(1632,1433), 0, 1);
    actions[29] = new EteindreBougie(Position(1878,1535), 0);
    actions[30] = new EteindreBougie(Position(2065,1722), 0, 1);
    actions[31] = new EteindreBougie(Position(2167,1910), 0);

    actions[32] = new RamasserVerre(Position(826,1910));
*/

    /*actionsToDo[0] = actions[0];
    actionsToDo[1] = actions[2];
    actionsToDo[2] = actions[1];
    actionsToDo[3] = actions[4];
    actionsToDo[4] = actions[5];
    actionsToDo[5] = actions[3];
    actionsToDo[6] = actions[9];
    actionsToDo[7] = actions[11];
    actionsToDo[8] = actions[10];
    actionsToDo[9] = actions[7];
    actionsToDo[10] = actions[8];
    actionsToDo[11] = actions[6];*/

    /*actionsToDo[12] = actions[12];
    actionsToDo[13] = actions[13];
    actionsToDo[14] = actions[14];
    actionsToDo[15] = actions[15];
    actionsToDo[16] = actions[16];
    actionsToDo[17] = actions[17];
    actionsToDo[18] = actions[18];
    actionsToDo[19] = actions[19];
    actionsToDo[20] = actions[20];
    actionsToDo[21] = actions[21];
    actionsToDo[22] = actions[22];
    actionsToDo[23] = actions[23];*/


    actions[0] = new RamasserVerre(Position(900,550));
    actions[1] = new RamasserVerre(Position(900,1050));
    actions[2] = new RamasserVerre(Position(1050,800));
    actions[3] = new RamasserVerre(Position(1200,550));
    /*actions[4] = new RamasserVerre(Position(1200,1050));
    actions[5] = new RamasserVerre(Position(1350,800));
    actions[6] = new RamasserVerre(Position(2100,550));
    actions[7] = new RamasserVerre(Position(2100,1050));
    actions[8] = new RamasserVerre(Position(1950,800));
    actions[9] = new RamasserVerre(Position(1800,550));
    actions[10] = new RamasserVerre(Position(1800,1050));
    actions[11] = new RamasserVerre(Position(1650,800));*/

    i=0;
    currentAction = actions[0];

    currentCommand = new CommandAllerA(currentAction->getRobotPosition());//currentAction->getRobotPosition());
    Asservissement::asservissement->setCommand(currentCommand);
    //hasToldBack = false;
    //numberOfGlassStored = 0;
    //mustComeToBase = false;
    setUp = true;
}

bool Strategie::update() {

    if (! setUp)
    return false;

    PositionPlusAngle pos_plus_angle = Odometrie::odometrie->getPos();
    Position pos = pos_plus_angle.getPosition();

    //Position goalPos = currentAction->getRobotPosition();

    // si on arrive trop prêt du mur, on y va a reculons
    /*if ( pos.getY() > 1820 && hasToldBack == false && goalPos.getY() > pos.getY())
    {
        currentCommand = new CommandGoTo(goalPos, true);
        Asservissement::asservissement->setCommand(currentCommand);
        hasToldBack = true;
    }*/



    //int result = currentAction->update();
/*
    if (result == -1)
    {

        MEDIUM_LEVEL_ACTION_TYPE actionType = currentAction->getType();
        if(actionType == RAMASSER_VERRE && numberOfGlassStored >0) // first bring glasses back
        {
            currentAction = new DeposerVerres(Position(isBlue?200:2800, pos.getY())); // bring back the glasses
            currentCommand = new CommandAllerA(currentAction->getRobotPosition());
        }
        else
        {
            i++; // update i only if we have done a regular action
            currentAction = actions[i];
            currentCommand = new CommandAllerA(currentAction->getRobotPosition());
        }
            i++; // update i only if we have done a regular action
            currentAction = actions[i];
            currentCommand = new CommandAllerA(currentAction->getRobotPosition());
        Asservissement::asservissement->setCommand(currentCommand);
        hasToldBack = false;
        if(i%2==0) {
        allumerLED();
        eteindreLED2();
        }
        else {
        eteindreLED();
        allumerLED2();
        }
    }
*/
    return true;
}

void Strategie::updateGoal(Position goalPos, bool goBack)
{
    currentCommand = new CommandAllerA(goalPos, goBack);
    Asservissement::asservissement->setCommand(currentCommand);
}

void Strategie::goToTarget() {
	PositionPlusAngle pos_plus_angle = Odometrie::odometrie->getPos();
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
Odometrie* Strategie::getOdometrie()
{
    return Odometrie::odometrie;
}

void Strategie::setMustMove(bool mustMove) {
	this->mustMove = mustMove;
}
void Strategie::setIsBlue(bool isBlue) {
	this->isBlue = isBlue;
}
void Strategie::storeGlass()
{
    this->numberOfGlassStored++;
}
void Strategie::cleanGlassStorage()
{
    this->numberOfGlassStored = 0;
}
bool Strategie::hasBeenSetUp()
{
    return setUp;
}
