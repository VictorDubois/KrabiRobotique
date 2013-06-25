#include "strategieV2.h"
#include "leds.h"
#include "positionPlusAngle.h"
#include "asservissement.h"
#include "memory.h"
#include "actionGoTo.h"
#include "recalibrerOdometrie.h"
#include "commandAllerA.h"
#include "ramasserVerres.h"
#include "eteindreBougies.h"
#include "marteaux.h"

#ifndef NULL
#define NULL 0
#endif

StrategieV2* StrategieV2::strategie = NULL;
int StrategieV2::updateCount = 0;
Command* StrategieV2::currentCommand = NULL;
MediumLevelAction* StrategieV2::currentAction = NULL;
int StrategieV2::actionsCount = 0;
MediumLevelAction* StrategieV2::actionsToDo[32];
SharpSensor* StrategieV2::sharps[10];
bool StrategieV2::hasToGoBase = false;
bool StrategieV2::hasJustAvoided = false;
bool StrategieV2::mustDeleteAction = false;
int StrategieV2::glassGathered = 0;
int StrategieV2::timeSinceLastRecalibration = 0;
bool StrategieV2::somethingDetected = false;
bool StrategieV2::isBlue = false;
bool StrategieV2::sharpsToCheck[SharpSensor::END_SHARP_NAME];
int StrategieV2::robotBloque = 0;
bool StrategieV2::enTrainDeRecalibrerOdometrie = false;
int StrategieV2::timer = 0;
MediumLevelAction* StrategieV2::evitement = NULL; 
bool StrategieV2::tourneSurSoiMeme = false;

StrategieV2::StrategieV2(bool blue)
{
    isBlue = blue;
    /*actionsToDo[0] = new RamasserVerreV2(Position(900,550));
    actionsToDo[1] = new RamasserVerreV2(Position(1050,800));
    actionsToDo[2] = new RamasserVerreV2(Position(900,1050));
    actionsToDo[3] = new RamasserVerreV2(Position(1200,1050));
    actionsToDo[4] = new RamasserVerreV2(Position(1200,550));
    actionsToDo[5] = new RamasserVerreV2(Position(1350,800));
    actionsToDo[6] = new RamasserVerreV2(Position(1650,800));
    actionsToDo[7] = new RamasserVerreV2(Position(1800,1050));
    actionsToDo[8] = new RamasserVerreV2(Position(1800,550));
    actionsToDo[9] = new RamasserVerreV2(Position(1950,800));
    actionsToDo[10] = new RamasserVerreV2(Position(2100,550));
    actionsToDo[11] = new RamasserVerreV2(Position(2100,1050));*/
    for (int i = 0; i < SharpSensor::END_SHARP_NAME; i++)
    {
        sharpsToCheck[i] = false;
    }

    //actionsToDo[0] = new Evitement();
    //actionsToDo[0] = new ActionGoTo(Position(1000,230), false);
    int decalage = 0;
    actionsToDo[0] = new EteindreBougies(isBlue); // action d'éteindre les bougies
    //actionsToDo[1] = new ActionGoTo(Position(400,1000), true);
    //actionsToDo[1] = new RecalibrerOdometrie(); //EteindreBougies(isBlue); // action d'éteindre les bougies
    actionsToDo[1] = new RamasserVerres(); //new ActionGoTo(Position(300,1300,StrategieV2::getIsBlue()), true); // //action de ramasser les verres
    
    //actionsToDo[0] = new ActionGoTo(Position(1200,550), false);//RamasserVerreV2(Position(900,550));
    //actionsToDo[1] = new ActionGoTo(Position(1200,700), false); // (400,230
                                                                    
    /*actionsToDo[2] = new ActionGoTo(Position(350,550), false); // (400,230
    //actionsToDo[2] = new ActionGoTo(Position(2600,400), false);
    actionsToDo[3] = new ActionGoTo(Position(2600,550), false);
    actionsToDo[4] = new ActionGoTo(Position(300, 550), false);
    actionsToDo[5] = new ActionGoTo(Position(2600,550), true);
    actionsToDo[6] = new ActionGoTo(Position(2600,800), false);
    actionsToDo[7] = new ActionGoTo(Position(300, 800), false);
    actionsToDo[8] = new ActionGoTo(Position(2600,800), true);
    actionsToDo[9] = new ActionGoTo(Position(2600,1070), false);
    actionsToDo[10] = new ActionGoTo(Position(300,1070), false);*/

    //currentAction = new RecalibrerOdometrie(new LimitSwitchSensor(LimitSwitchSensor::BACK_LEFT, GPIO_Pin_14, GPIOD), new LimitSwitchSensor(LimitSwitchSensor::BACK_RIGHT, GPIO_Pin_1, GPIOD));
    currentAction = actionsToDo[actionsCount];
    //currentCommand = new CommandAllerA(currentAction->getGoalPosition());
    //Asservissement::setCommand(currentCommand);
    //currentAction = new RecalibrerOdometrie();
    //hasJustAvoided = true;
    //currentAction->update();

    StrategieV2::strategie = this;
    
    uint8_t channels[10] = {9,13,8,11,5,10,4,12,14,15};
    uint16_t* data = AnalogSensor::initialiserADC(10, channels);
    int nbSharp = 10;
    sharps[0] = new SharpSensor(SharpSensor::FRONT_LEFT, 9, data, 2000.0); // front left 9
    sharps[1] = new SharpSensor(SharpSensor::FRONT_RIGHT, 13, data); // front side right 13
    sharps[2] = new SharpSensor(SharpSensor::FRONT_SIDE_LEFT, 8, data); // front side left 8
    sharps[3] = new SharpSensor(SharpSensor::FRONT_SIDE_RIGHT, 11, data); // avant side droite 11
    sharps[4] = new SharpSensor(SharpSensor::BACK_LEFT, 5, data); // ARRIERE gauche 5
    sharps[5] = new SharpSensor(SharpSensor::BACK_MIDDLE, 10, data, 2500.); // back middle 10
    sharps[6] = new SharpSensor(SharpSensor::NONE, 4, data); // 
    sharps[7] = new SharpSensor(SharpSensor::ELEVATOR_TOP, 12, data); // capteur haut ascenseur 12
    sharps[8] = new SharpSensor(SharpSensor::ELEVATOR_DOWN, 14, data); // capteur bas ascenseur 14
    sharps[9] = new SharpSensor(SharpSensor::BACK_RIGHT, 15, data, 2000.0); // 
    
    emptySharpsToCheck();
    enableSharp(SharpSensor::FRONT_LEFT);
    enableSharp(SharpSensor::FRONT_RIGHT);
    enableSharp(SharpSensor::FRONT_SIDE_LEFT);
    enableSharp(SharpSensor::FRONT_SIDE_RIGHT);
    
    enableSharp(SharpSensor::BACK_LEFT);
    enableSharp(SharpSensor::BACK_MIDDLE);
    enableSharp(SharpSensor::BACK_RIGHT);
    
    updateCount = 0;
}

StrategieV2::~StrategieV2()
{
    //dtor
}


void StrategieV2::update()
{
    if (StrategieV2::strategie == NULL)
        return;
    updateCount++;
    if (updateCount < 0)
    {
        updateCount = 50000;
    }
    if ((updateCount / 100) % 2)
    {
        allumerLED2();
        if (updateCount > 18000)
            eteindreLED();
    }
    else 
    {
        eteindreLED2();
        if (updateCount > 18000)
            allumerLED();
    }
    if (updateCount <= 18000)
    {
        
    }
    if (updateCount >= 18000)
    {
        Asservissement::asservissement->setCommandSpeeds(NULL);
        return;
    }
    //if (updateCount > 6000 && updateCount < 10000) // attendre 15 secondes
    /*{
        Asservissement::asservissement->setCommandSpeeds(NULL);
        return;
    }*/
    if (actionsCount >= 2)
        return;
    if (robotBloque > 1000)
        return;
/*
    enableSharp(SharpSensor::FRONT_LEFT);
    enableSharp(SharpSensor::FRONT_RIGHT);
    enableSharp(SharpSensor::FRONT_SIDE_LEFT);
    enableSharp(SharpSensor::FRONT_SIDE_RIGHT);
    enableSharp(SharpSensor::BACK_LEFT);
    enableSharp(SharpSensor::BACK_MIDDLE);
    enableSharp(SharpSensor::BACK_RIGHT);
    */
    //std::cout << "update" << std::endl;
    // check sensors:
        AnalogSensor::startConversion();
        //allumerLED2();
        for (int i = 0; i < SharpSensor::END_SHARP_NAME; i++) // update tous les sharps
        {
            sharps[i]->updateValue();
        }
            //sharps[9]->updateValue();
        bool allume = false;
        for (int i = 0; i < SharpSensor::END_SHARP_NAME; i++)
        {
            if (sharpsToCheck[i] && !tourneSurSoiMeme && i != SharpSensor::BACK_RIGHT)
            {
                if (sharps[i]->getValue().b)
                {
                    //allume = true;
                }
            }
        }
            //if (sharps[9]->getValue().b)
            //{
                //allume = true;
            //}
        if (allume) {
            allumerLED();
        }
        else {
            eteindreLED();
        }
    //return;
    //somethingDetected = Sensors::getSensors()->sharpDetect();
        
    //allumerLED2();
    if (allume)
    {
        hasJustAvoided = true;
        Asservissement::asservissement->setCommandSpeeds(NULL);
        //allumerLED();
        /*
        if (true) // if (canStillDoAction)
        {
            if (currentAction)
            {
                currentAction->collisionAvoided();
                currentAction->update();
            }
        }
        hasJustAvoided = false;
        somethingDetected = false;
        */
        // tentative d'évitement :
        
        float currentAngle = wrapAngle(Odometrie::odometrie->getPos().getAngle());
        Position pos = Odometrie::odometrie->getPos().getPosition();
        Position newPos = pos + Position(-200*cos(currentAngle), -200*sin(currentAngle));
        Position newPos2 = pos + Position(200*cos(currentAngle), 200*sin(currentAngle));
        bool hasAvoided = false;
        /*if (newPos.getX() > 300 && newPos.getX() < 2700 && newPos.getY() > 300 && newPos.getY() < 1800)
        {
            Position vect2 = newPos - Position(1500,2000);
            if (vect2.getNorme() > 600)
            {
                bool avance = false;
                bool bouge = false;
                if (sharpDetects(SharpSensor::FRONT_LEFT) || sharpDetects(SharpSensor::FRONT_RIGHT) || sharpDetects(SharpSensor::FRONT_SIDE_LEFT) || sharpDetects(SharpSensor::FRONT_SIDE_LEFT))
                {
                    bouge = true;
                    avance = false;
                }
                if (sharpDetects(SharpSensor::BACK_LEFT) || sharpDetects(SharpSensor::BACK_RIGHT) || sharpDetects(SharpSensor::BACK_MIDDLE))
                {
                    bouge = false;
                }
                if (bouge)
                {
                    hasAvoided = true;
                    addTemporaryAction(new ActionGoTo(newPos, !avance));
                    Marteaux::enfoncerBasDroit();
                }
            }
        }
        if (newPos2.getX() > 300 && newPos2.getX() < 2700 && newPos2.getY() > 300 && newPos2.getY() < 1800 && !hasAvoided)
        {
            Position vect2 = newPos2 - Position(1500,2000);
            if (vect2.getNorme() > 600)
            {
                bool avance = false;
                bool bouge = false;
                if (sharpDetects(SharpSensor::FRONT_LEFT) || sharpDetects(SharpSensor::FRONT_RIGHT) || sharpDetects(SharpSensor::FRONT_SIDE_LEFT) || sharpDetects(SharpSensor::FRONT_SIDE_LEFT))
                {
                    bouge = true;
                    avance = false;
                }
                if (sharpDetects(SharpSensor::BACK_LEFT) || sharpDetects(SharpSensor::BACK_RIGHT) || sharpDetects(SharpSensor::BACK_MIDDLE))
                {
                    bouge = false;
                }
                if (bouge)
                {
                    hasAvoided = true;
                    addTemporaryAction(new ActionGoTo(newPos2, avance));
                    Marteaux::enfoncerBasDroit();
                }
            }
        }*/
        //if (!hasAvoided)
            return;
    }
    else
    {
        if (hasJustAvoided == true)
        {
            hasJustAvoided = false;
            if (currentCommand)
                currentCommand->resetSpeeds();
        }
    }
    //allumerLED2();
    //currentCommand->update();
    //std::cout << "updating action" << std::endl;
    if (abs(Odometrie::odometrie->getVitesseLineaire()) < 0.0001 && abs(Odometrie::odometrie->getVitesseLineaire()) < 0.00001 && abs(Asservissement::asservissement->getLinearSpeed()) > 0.1)//0.01*abs(Asservissement::asservissement->getLinearSpeed())) //*abs())
        robotBloque = 0;// ++;
    else 
        robotBloque = 0;
    if (currentAction->update() == -1 || (robotBloque > 1000))// && !enTrainDeRecalibrerOdometrie))
    {
        if (robotBloque > 1000) // si le robot est bloqué 2 secondes
        {
            // on recule de 20 cm
            Asservissement::asservissement->setCommandSpeeds(NULL);
            currentCommand = NULL;
            actionsCount = 2;
            bool mustGoBack = true;
            allumerLED();
            //StrategieV2::addTemporaryAction(new ActionGoTo(Odometrie::odometrie->getPos().getPosition(), mustGoBack));
        }
        robotBloque = 0;
        //std::cout << "Changing action" << std::endl;
        Position currentPos = Odometrie::odometrie->getPos().getPosition();
        // delete the current command
        //if (currentCommand != NULL)
            //delete currentCommand;
        //if (mustDeleteAction && currentAction != NULL)
            //delete currentAction;

        // must go to base :
        /*if (hasToGoBase)
        {
            currentAction = new RamenerVerres(Position(300,currentPos.getY()));
            hasToGoBase = false;
            mustDeleteAction = true;
        }*/
        /*else if (timeSinceLastRecalibration % 3 == 2)
        {
            currentAction = new RecalibrerOdometrie();
            mustDeleteAction = true;
            timeSinceLastRecalibration++;
        }*/
        //else
        //{
        if (mustDeleteAction) // temporary action
            mustDeleteAction = false;
        else       
            actionsCount++;
            
        if (actionsCount == 2)
        {
            currentCommand = NULL;
            Asservissement::asservissement->setCommandSpeeds(NULL);
            updateCount = 17000;
            return;
        }
        else
        {
            currentAction = actionsToDo[actionsCount];
        }
            //timeSinceLastRecalibration++;
        //}
        // != NULL)
            //delete action;
        //if (currentAction)
           // currentAction->update();

    }
    if (currentCommand)
        currentCommand->update();
    Asservissement::asservissement->setCommandSpeeds(currentCommand);
//    updateCount ++;
    eteindreLED2();
    eteindreLED();
}

void StrategieV2::setCurrentGoal(Position goal, bool goBack, float maxSpeed)
{
    if (currentCommand != NULL)
        delete currentCommand;
    if (actionsCount == 0)
        currentCommand = new CommandAllerA(goal, goBack, maxSpeed/2);
    else 
        currentCommand = new CommandAllerA(goal, goBack, maxSpeed);
    Asservissement::asservissement->setCommandSpeeds(currentCommand);
    StrategieV2::emptySharpsToCheck();
    if (goBack)
    {
        StrategieV2::sharpsToCheck[SharpSensor::BACK_LEFT] = true;
        StrategieV2::sharpsToCheck[SharpSensor::BACK_MIDDLE] = true;
        StrategieV2::sharpsToCheck[SharpSensor::BACK_RIGHT] = true;
    }
    else 
    {
        StrategieV2::sharpsToCheck[SharpSensor::FRONT_LEFT] = true;
        StrategieV2::sharpsToCheck[SharpSensor::FRONT_RIGHT] = true;
        StrategieV2::sharpsToCheck[SharpSensor::FRONT_SIDE_LEFT] = true;
        StrategieV2::sharpsToCheck[SharpSensor::FRONT_SIDE_RIGHT] = true;
    }
}
void StrategieV2::setCurrentGoal(Position goal, Position center, float vitesse, bool goBack)
{
    if (currentCommand != NULL)
            delete currentCommand;
    currentCommand = new CommandAllerEnArcA(goal, center, vitesse*5, goBack);
    Asservissement::asservissement->setCommandSpeeds(currentCommand);
}
void StrategieV2::lookAt(Position pos)
{
    if (currentCommand != NULL)
            delete currentCommand;
    currentCommand = new CommandTournerVers(pos); // create the command
    Asservissement::asservissement->setCommandSpeeds(currentCommand); // apply it
    StrategieV2::emptySharpsToCheck();
}
void StrategieV2::addTemporaryAction(MediumLevelAction* action)
{
    currentAction = action;
    mustDeleteAction = true; // this is a temporary action that needs to be deleted
}
void StrategieV2::setJustAvoided(bool avoided)
{
    hasJustAvoided = avoided;
}
bool StrategieV2::getJustAvoided()
{
    return hasJustAvoided;
}
bool StrategieV2::willCollide()
{
    somethingDetected = true;
    Asservissement::asservissement->setCommandSpeeds(NULL); // stoppe le robot
}

void StrategieV2::setIsBlue(bool blue)
{
    isBlue = blue;
}
bool StrategieV2::getIsBlue()
{
    return isBlue;
}

void StrategieV2::gatherGlass()
{
    glassGathered++;
    if (glassGathered > 0)
    {
        glassGathered = 0;
        hasToGoBase = true;
    }
}

void StrategieV2::setEnTrainDeRecalibrer(bool recalibre)
{
    enTrainDeRecalibrerOdometrie = recalibre;
}

void StrategieV2::emptySharpsToCheck()
{
    for (int i = 0; i < SharpSensor::END_SHARP_NAME; i++)
        sharpsToCheck[i] = false;
}
void StrategieV2::enableSharp(SharpSensor::SharpName name)
{
    for (int i = 0; i < SharpSensor::END_SHARP_NAME; i++)
        if (sharps[i]->getName() == name)
            sharpsToCheck[i] = true;
}

void StrategieV2::setCommand(Command* command)
{
    currentCommand = command;
}

bool StrategieV2::sharpDetects(SharpSensor::SharpName name)
{
    for (int i = 0; i < SharpSensor::END_SHARP_NAME; i++)
        if (sharps[i]->getName() == name && sharpsToCheck[i] == true && !tourneSurSoiMeme)
            return sharps[i]->getValue().b;
}

void StrategieV2::setTourneSurSoiMeme(bool tourne)
{
    tourneSurSoiMeme = tourne;
}
