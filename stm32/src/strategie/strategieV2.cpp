#include "strategieV2.h"
#if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // H405
    #include "krabijunior2015.h"
#else
    #include "krabi2015.h"
#endif
#include "leds.h"
#include "positionPlusAngle.h"
#include "asservissement.h"
#ifdef ROBOTHW
    #include "memory.h"
#endif
#include "actionGoTo.h"
#include "recalibrerOdometrie.h"

#include "commandAllerA.h"
#include "commandAllerEnArcA.h"
#include "commandTournerVers.h"

#include "sensors.h"

#ifndef NO_REMOTE
    #include "remote.h"
#endif

#ifdef ROBOTHW
    #include "tourelle.h"
    #include "tirette.h"
#else
    #include <QDebug>
#endif
//#include <iostream>

#ifndef NULL
#define NULL 0
#endif

StrategieV2* StrategieV2::strategie = NULL;

int StrategieV2::updateCount = 0;
Command* StrategieV2::currentCommand = NULL;
MediumLevelAction* StrategieV2::currentAction = NULL;
int StrategieV2::actionsCount = 0;
MediumLevelAction* StrategieV2::actionsToDo[32];
SharpSensor** StrategieV2::sharps;
bool StrategieV2::hasToGoBase = false;
bool StrategieV2::hasJustAvoided = false;
bool StrategieV2::mustDeleteAction = false;
bool StrategieV2::hasToStopAfterAction = false;
int StrategieV2::glassGathered = 0;
int StrategieV2::timeSinceLastRecalibration = 0;
bool StrategieV2::somethingDetected = false;
bool StrategieV2::yellow = true;
bool StrategieV2::sharpsToCheck[SharpSensor::END_SHARP_NAME];
int StrategieV2::robotBloque = 0;
bool StrategieV2::enTrainDeRecalibrerOdometrie = false;
int StrategieV2::timer = 0;
MediumLevelAction* StrategieV2::evitement = NULL;
bool StrategieV2::tourneSurSoiMeme = false;
int StrategieV2::timeToRestart = 0;

#ifdef ROBOTHW
Tourelle* StrategieV2::tourelle = NULL;
int StrategieV2::hysteresisTourelle = 0;
#endif

StrategieV2::StrategieV2(bool yellow)
{
    if(strategie == 0)
    {
        StrategieV2::setYellow(yellow);
        timeToRestart = 0;

        for (int i = 0; i < SharpSensor::END_SHARP_NAME; i++)
            sharpsToCheck[i] = false;

        int decalage = 0;

    #if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // H405
        actionsToDo[0] = (MediumLevelAction*) new KrabiJunior2015(yellow);
    #else
        actionsToDo[0] = (MediumLevelAction*) new Krabi2015(yellow);
    #endif

        currentAction = actionsToDo[actionsCount];


        StrategieV2::strategie = this;

        Sensors* sensors = Sensors::getSingleton();
        sharps = sensors->getSharpSensorsList();

        emptySharpsToCheck();
#ifdef ROBOTHW
//        tourelle = new Tourelle(TIM6, 0);//TIM parameter is not implemented yet
    tourelle = new Tourelle();
    //tourelle->setZoneCritique(10, 27000);
#endif

        updateCount = 0;
    }


}

StrategieV2::~StrategieV2()
{
    //dtor
}

long StrategieV2::getTimeSpent()
{
    return updateCount * 5;
}

void StrategieV2::resetTime()
{
    updateCount = 0;
}


void StrategieV2::update()
{
#ifndef NO_REMOTE
    Remote::getSingleton()->update();
#endif

    if (!currentAction)
    {
        Asservissement::asservissement->setCommandSpeeds(NULL);
        return;
    }
    //Tourelle* tourelle = new Tourelle(TIM6, 0);
    /*
        uint8_t resultZoneCritique = tourelle->setZoneCritique(10, 27000);



        uint16_t resultAngle = tourelle->calculAngle(0);

    //    objectDetectionInstant[0] = 0;
    //    resultAngle = tourelle->calculAngle(0);
    //    objectDetectionInstant[0] = 10;
    //    resultAngle = tourelle->calculAngle(0);
    //    objectDetectionInstant[0] = 20;
    //    resultAngle = tourelle->calculAngle(0);
    //    objectDetectionInstant[0] = 40;
    //    resultAngle = tourelle->calculAngle(0);

        bool resultUpdate = tourelle->update();

        resultUpdate = tourelle->update();

        nombreObjetDetecte = 1;

        resultUpdate = tourelle->update();

    */

    if (StrategieV2::strategie == NULL)
        return;
    updateCount++;

    if(currentAction)
        currentAction->updateTime(90*1000-updateCount*5);

#ifdef ROBOTHW
//    if (updateCount % 6 == 2)
//    {
//        EXTI_GenerateSWInterrupt(EXTI_Line2);
//    }

//    if (updateCount % 6 == 3)
//    {
//        EXTI_GenerateSWInterrupt(EXTI_Line3);
//    }

    //On met à jour l'indicateur de "on doit rallentir"
//    bool returnTourelle = tourelle->updateSimple();
//    if(returnTourelle)
//    {
//        //allumerLED();
//        hysteresisTourelle = 100;// On ralenti pendant 0,5s mini
//    }
//    else if (hysteresisTourelle > 0)
//    {
//        hysteresisTourelle--;
//    }
//
//    //On donne l'ordre de ralentir, si besoin
//    currentCommand->limitSpeed(hysteresisTourelle);

#endif
    if (updateCount < 0)
    {
        updateCount = 50000;
    }

    //TIR FILET
/*#ifdef KRABI
    if(updateCount > 18200 && updateCount < 18210)
        //if(updateCount > 3000 && updateCount < 3010)
    {
        //On tire
        CanonFilet::getSingleton()->shoot();
#ifndef ROBOTHW
        qDebug() << "CanonFilet::getSingleton()->shoot();";
#endif

    }
#endif
*/
#ifndef ROBOTHW
    //qDebug() << updateCount;
#endif

//    if (updateCount > 677)//684)
//    {
//        updateCount++;
//        updateCount--;
//    }

    /*if ((updateCount / 100) % 2)
    {
        //allumerLED2();
        if (updateCount > 18000)
            eteindreLED();

    }
    else
    {
        //eteindreLED2();
        if (updateCount > 18000)
            allumerLED();
    }*/

    if (updateCount <= 10000)
    {

    }
    else if (updateCount >= 10000)
    {
        Asservissement::asservissement->setCommandSpeeds(NULL);
        eteindreLED();
        return;
    }
    //if (updateCount > 6000 && updateCount < 10000) // attendre 15 secondes
    /*{
        Asservissement::asservissement->setCommandSpeeds(NULL);
        return;
    }*/
    if (actionsCount >= 1)
    {
        updateCount = 20000;
        return;
    }
    /*if (robotB1loque > 1000)
        return;*/
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

    //

    //allumerLED2();
    for (int i = 0; i < SharpSensor::END_SHARP_NAME; i++) // update tous les sharps
    {
        sharps[i]->updateValue();
    }
    //sharps[9]->updateValue();
    bool allume = false;
    for (int i = 0; i < SharpSensor::END_SHARP_NAME; i++)
    {
        if (/*sharpsToCheck[i] && !tourneSurSoiMeme*/true)
        {
            if (sharps[i]->getValue().b)
            {
                if(Odometrie::odometrie->getPos().getPosition().getY()>1600)//Si on est en train de faire les claps
                {
                    allume = false;//true;//Sharps desactivés
                }
                else{
                    allume = true;
                }
            }
        }
    }

    float values[10] = {0};
    bool detected[10] = {false};

    //allumerLED2();
    for (int i = 0; i < 8; i++)
    {
        values[i] = sharps[i]->getValue().f;
        detected[i] = sharps[i]->getValue().b;
        /*if (i!=5 && i!=7 && detected[i])
            allume = true;*/
    }


    //allume = false;
//bool allume = false;
    //if (sharps[9]->getValue().b)
    //{
    //allume = true;
    //}

    //Remote::getSingleton()->update();

    /*if (Remote::getSingleton()->isRemoteMode())
    {
        updateCount = 10;
        Led::setOff(1);
    }
    else
    {*/
        Led::setOn(1);

        if (allume)
        {
            Asservissement::asservissement->setCommandSpeeds(NULL);
            Asservissement::asservissement->update();
            allumerLED2();
#ifndef NO_REMOTE
            //Remote::getSingleton()->log("Detect !");
#endif
        }
        else
        {
            eteindreLED2();
#ifndef NO_REMOTE
            //Remote::getSingleton()->log("No !");
#endif
        }
        //return;
        //somethingDetected = Sensors::getSensors()->sharpDetect();

        //allumerLED2();

        //allume = true;//(updateCount%30==0);
        //allume = false;
        if(timeToRestart)
        {
            timeToRestart--;
        }
        if(timeToRestart == 1)//Dernière boucle d'évitement avant de repartir
        {
            if (currentAction)
            {
                //Pour changer de trajectoire, décommenter les lignes suivantes
                currentAction->collisionAvoided();
                actionsToDo[actionsCount]->collisionAvoided();
//                currentCommand->collisionAvoided();
                currentAction->update();
                Position pos = Odometrie::odometrie->getPos().getPosition();
                addTemporaryAction(new ActionGoTo(pos, true));

                //On arrête le robot
                if (currentCommand)
                    currentCommand->resetSpeeds();
            }
            timeToRestart--;
        }

        else if (allume || timeToRestart) // Si un des sharp voit un adversaire, ou qu'on doit être arrêté suite à une détection
        {
            if(!timeToRestart)//Début de l'évitement
            {
                timeToRestart = 400;
                hasJustAvoided = true;
                //Asservissement::asservissement->setCommandSpeeds(NULL); // On s'arrête
                //allumerLED();

//            if (true) // if (canStillDoAction)
//            {

//            }
                hasJustAvoided = false;
                somethingDetected = false;
                //
                // tentative d'évitement :
                //Position pos = Odometrie::odometrie->getPos().getPosition();
                //addTemporaryAction(new ActionGoTo(pos, true));

            }
            Asservissement::asservissement->setCommandSpeeds(NULL);
            Asservissement::asservissement->resetAsserv();
            //Asservissement::asservissement->setCommandSpeeds(currentCommand);

            /*
                    float currentAngle = wrapAngle(Odometrie::odometrie->getPos().getAngle());
                    Position pos = Odometrie::odometrie->getPos().getPosition();
                    Position newPos = pos + Position(-200*cos(currentAngle), -200*sin(currentAngle));
                    Position newPos2 = pos + Position(200*cos(currentAngle), 200*sin(currentAngle));
                    bool hasAvoided = false;
                    if (newPos.getX() > 300 && newPos.getX() < 2700 && newPos.getY() > 300 && newPos.getY() < 1800)
                    {
                        Position vect2 = newPos - Position(1500,2000);
                        if (vect2.getNorme() > 600)
                        {
                            bool avance = false;
                            bool bouge = false;
                            if (sharpDetects(SharpSensor::FRONT_LEFT) || sharpDetects(SharpSensor::FRONT_RIGHT) || sharpDetects(SharpSensor::FRONT_SIDE_LEFT) || sharpDetects(SharpSensor::FRONT_SIDE_RIGHT))
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
                                #ifndef ROBOTHW
                                    qDebug() << "newPos" << updateCount << "\n";
                                #endif
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
                            if (sharpDetects(SharpSensor::FRONT_LEFT) || sharpDetects(SharpSensor::FRONT_RIGHT) || sharpDetects(SharpSensor::FRONT_SIDE_LEFT) || sharpDetects(SharpSensor::FRONT_SIDE_RIGHT))
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
                                #ifndef ROBOTHW
                                    qDebug() << "newPos2" << updateCount << "\n";
                                #endif
                                Marteaux::enfoncerBasDroit();
                            }
                        }
                    }
                    if (!hasAvoided)
                    {
                        allumerLED();
                        return;
                    }// */
     //   }
    }
//    else
//    {
////        if (hasJustAvoided == true)
////        {
////            hasJustAvoided = false;
//            if (currentCommand)
//                currentCommand->resetSpeeds();
////        }
//    }
    //allumerLED2();
    //currentCommand->update();
    //std::cout << "updating action" << std::endl;
    /*if (abs(Odometrie::odometrie->getVitesseLineaire()) < 0.0001 && abs(Odometrie::odometrie->getVitesseLineaire()) < 0.0001 && abs(Asservissement::asservissement->getLinearSpeed()) > 0.1)//0.01*abs(Asservissement::asservissement->getLinearSpeed())) // *abs())
    {
        //robotBloque++;// ++;
        //std::cout << robotBloque << "\n";
    }*/

//    else
//        robotBloque = 0;
    if (currentAction->update() == -1 || (robotBloque > 50))// && !enTrainDeRecalibrerOdometrie))
    {
        if (robotBloque > 1000) // si le robot est bloqué 2 secondes
        {
            // on recule de 20 cm
            Asservissement::asservissement->setCommandSpeeds(NULL);
            Asservissement::asservissement->resetAsserv();
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

        if (hasToStopAfterAction)
        {
            hasToStopAfterAction = false;
            Asservissement::asservissement->stop();
        }

        if (mustDeleteAction) // temporary action
            mustDeleteAction = false;
        else
            actionsCount++;


        if (actionsCount == 2)
        {
            currentCommand = NULL;
            Asservissement::asservissement->setCommandSpeeds(NULL);
            Asservissement::asservissement->resetAsserv();
            updateCount = 170000;//17000;
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
    if(!timeToRestart)
    {
        if (currentCommand)
            currentCommand->update();
        Asservissement::asservissement->setCommandSpeeds(currentCommand);
    }
//    updateCount ++;
    //eteindreLED2();
    //eteindreLED();
}

Command* StrategieV2::setCurrentGoal(Position goal, bool goBack, float maxSpeed, Angle precisionAngle, float stopAtDistance)
{
    if (currentCommand != NULL)
        delete currentCommand;

//    if (actionsCount == 0)
//        currentCommand = new CommandAllerA(goal, goBack, maxSpeed/2);
//    else
    currentCommand = new CommandAllerA(goal, goBack, maxSpeed, 0.0f, precisionAngle, stopAtDistance);
    Asservissement::asservissement->setCommandSpeeds(currentCommand);
    StrategieV2::emptySharpsToCheck();
    //TODO
#ifdef KRABI
    /*if (goBack)
    {
        //StrategieV2::sharpsToCheck[SharpSensor::BACK_LEFT] = true;
        //StrategieV2::sharpsToCheck[SharpSensor::LEFT_BACK] = true;
        StrategieV2::sharpsToCheck[SharpSensor::BACK_RIGHT] = true;
        StrategieV2::sharpsToCheck[SharpSensor::FRONT_LEFT] = false;
        //StrategieV2::sharpsToCheck[SharpSensor::RIGHT_BACK] = true;
    }
    else
    {
        StrategieV2::sharpsToCheck[SharpSensor::FRONT_LEFT] = true;
        StrategieV2::sharpsToCheck[SharpSensor::BACK_RIGHT] = false;
        //StrategieV2::sharpsToCheck[SharpSensor::FRONT_RIGHT] = true;
        //StrategieV2::sharpsToCheck[SharpSensor::LEFT_FRONT] = true;
        //StrategieV2::sharpsToCheck[SharpSensor::RIGHT_FRONT] = true;
    }*/
#endif

    return currentCommand;
}

Command* StrategieV2::setCurrentGoalSmooth(Position goal, Position nextGoal, float smoothFactor, bool goBack, float maxSpeed, Angle precisionAngle)
{
    if (currentCommand != NULL)
        delete currentCommand;

    CommandAllerA* command = new CommandAllerA(goal, goBack, maxSpeed, 0.0f, precisionAngle);
    command->smoothMovement(nextGoal, smoothFactor);
    currentCommand = command;

    Asservissement::asservissement->setCommandSpeeds(currentCommand);
    StrategieV2::emptySharpsToCheck();

    return currentCommand;
}

Command* StrategieV2::setCurrentGoal(Position goal, Position center, float vitesse, bool goBack, Angle precisionAngle)
{
    if (currentCommand != NULL)
        delete currentCommand;
    currentCommand = new CommandAllerEnArcA(goal, center, vitesse*5, goBack);
    Asservissement::asservissement->setCommandSpeeds(currentCommand);

    return currentCommand;
}

void StrategieV2::stop()
{
    if (currentCommand != NULL)
        delete currentCommand;
    currentCommand = NULL;
}

Command* StrategieV2::lookAt(Position pos, float maxSpeed)
{
    if (currentCommand != NULL)
        delete currentCommand;
    currentCommand = new CommandTournerVers(pos, maxSpeed); // create the command
    Asservissement::asservissement->setCommandSpeeds(currentCommand); // apply it
    StrategieV2::emptySharpsToCheck();

    return currentCommand;
}
Command* StrategieV2::lookAt(Angle a, float maxSpeed)
{
    if (currentCommand != NULL)
        delete currentCommand;
    currentCommand = new CommandTournerVers(a, maxSpeed); // create the command
    Asservissement::asservissement->setCommandSpeeds(currentCommand); // apply it
    StrategieV2::emptySharpsToCheck();

    return currentCommand;
}
void StrategieV2::addTemporaryAction(MediumLevelAction* action, bool stopAfter)
{
    currentAction = action;
    mustDeleteAction = true; // this is a temporary action that needs to be deleted
    hasToStopAfterAction = stopAfter;
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
    Asservissement::asservissement->resetAsserv();
}

bool StrategieV2::isYellow()
{
    return yellow;
}

void StrategieV2::setYellow(bool yellow)
{
    StrategieV2::yellow = yellow;
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

void StrategieV2::enableSharpsGroup(bool front)
{
    emptySharpsToCheck();

    if (front)
    {
#if defined(STM32F40_41xxx)
        enableSharp(SharpSensor::FRONT_LEFT);
        enableSharp(SharpSensor::FRONT_RIGHT);
        enableSharp(SharpSensor::FRONT_MIDDLE);
#else
        enableSharp(SharpSensor::FRONT_LEFT);
        enableSharp(SharpSensor::FRONT_RIGHT);
        enableSharp(SharpSensor::FRONT_LEFT_SIDE);
        enableSharp(SharpSensor::FRONT_RIGHT_SIDE);
#endif
    }
    else
    {
#if defined(STM32F40_41xxx)
        enableSharp(SharpSensor::BACK_LEFT);
        enableSharp(SharpSensor::BACK_RIGHT);
        enableSharp(SharpSensor::BACK_MIDDLE);
#else
        enableSharp(SharpSensor::BACK_LEFT);
        enableSharp(SharpSensor::BACK_RIGHT);
        enableSharp(SharpSensor::BACK_LEFT_SIDE);
        enableSharp(SharpSensor::BACK_RIGHT_SIDE);
#endif
    }

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

SharpSensor** StrategieV2::getSensors()
{
    return sharps;
}

#ifndef ROBOTHW
void StrategieV2::paint(QPainter* p)
{
    actionsToDo[actionsCount]->paint(p);
}

bool* StrategieV2::getSharpsToCheck()
{
    return sharpsToCheck;
}

#endif
