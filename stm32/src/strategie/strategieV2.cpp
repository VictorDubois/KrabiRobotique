#include "strategieV2.h"
#include "krabi2015.h"
//#include "krabijunior2015.h"
#include "leds.h"
#include "positionPlusAngle.h"
#include "asservissement.h"
#ifdef ROBOTHW
#include "memory.h"
#endif
#include "actionGoTo.h"
#include "recalibrerOdometrie.h"
#include "commandAllerA.h"

#include "sensors.h"
#include "remote.h"

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
int StrategieV2::timeToRestart = 0;

#ifdef ROBOTHW
Tourelle* StrategieV2::tourelle = NULL;
int StrategieV2::hysteresisTourelle = 0;
#endif

StrategieV2::StrategieV2(bool blue)
{
    isBlue = blue;
    timeToRestart = 0;
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
        sharpsToCheck[i] = false;

    //actionsToDo[0] = new Evitement();
    //actionsToDo[0] = new ActionGoTo(Position(1000,230), false);
    int decalage = 0;
    //actionsToDo[0] = new RecalibrerOdometrie(true);
    //actionsToDo[0] = new RecalibrerOdometrie(blue, Position(200, 1500, blue), RecalibrerOdometrie::COTE_NOTRE_DEPART_HAUT);
    //actionsToDo[1] = new RecalibrerOdometrie(blue, Position(500, 500, blue), RecalibrerOdometrie::COTE_NOTRE_DEPART_BAS);
    //actionsToDo[2] = new RecalibrerOdometrie(blue, Position(2500, 500, blue), RecalibrerOdometrie::COTE_DEPART_ADVERSAIRE_BAS);
    //actionsToDo[3] = new RecalibrerOdometrie(blue, Position(2800, 1500, blue), RecalibrerOdometrie::COTE_DEPART_ADVERSAIRE_HAUT);
    //actionsToDo[0] = new StrategieV3(blue);

    /* Appel des stratégies */

    //actionsToDo[0] = (MediumLevelAction*) new Krabi2014(blue);
    actionsToDo[0] = (MediumLevelAction*) new Krabi2015(blue);
    //actionsToDo[0] = (MediumLevelAction*) new KrabiJunior2015(blue);

    // 2014 :
    //CanonFilet::getSingleton()->attente();

    //actionsToDo[0] = new Fresque(blue, Position(1500, 1500));


    /*###############################################
    Benchmark strategieV3
    ###############################################

    #ifdef STM32F10X_CL
        Tirette tirette(GPIOE, GPIO_Pin_5);
    #elif defined(STM32F10X_MD) || defined(STM32F40_41xxx)
        Tirette tirette(GPIOA, GPIO_Pin_10);
    #endif


    StrategieV3 strategieV3 = new StrategieV3(true);


    allumerLED();
    eteindreLED();
    allumerLED2();
    eteindreLED2();
    allumerLED();
    tirette.attendreRemise();
    tirette.attendreEnlevee();
    eteindreLED();
    tirette.attendreRemise();
    tirette.attendreEnlevee();
        allumerLED();
    tirette.attendreRemise();
    tirette.attendreEnlevee();
    eteindreLED();



    for(int i = 0 ; i < 100000 ; i++)
    {
        if(i%ROBOT_VU_ICI==0)
        {
            strategieV3.resetEverything();
        }
        strategieV3.update();
    }
    allumerLED();
    tirette.attendreRemise();
    tirette.attendreEnlevee();
    eteindreLED();
    tirette.attendreRemise();
    tirette.attendreEnlevee();
    allumerLED();
    tirette.attendreRemise();
    tirette.attendreEnlevee();
    eteindreLED();
    tirette.attendreRemise();
    tirette.attendreEnlevee();
    allumerLED();
    tirette.attendreRemise();
    tirette.attendreEnlevee(); // */
//    actionsToDo[0] = new EteindreBougies(isBlue); // action d'éteindre les bougies
//    actionsToDo[1] = new ActionGoTo(Position(400,1000), true);
    //actionsToDo[1] = new RecalibrerOdometrie(); //EteindreBougies(isBlue); // action d'éteindre les bougies
//    actionsToDo[1] = new RamasserVerres(); //new ActionGoTo(Position(300,1300,StrategieV2::getIsBlue()), true); // //action de ramasser les verres
//    actionsToDo[0] = new ActionGoTo(Position(1200, 1000, isBlue), false);
//    actionsToDo[1] = new ActionGoTo(Position(800, 1000, isBlue), false);
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

    //#ifndef ROBOTHW //liste utilisée pour simuler les capteurs

    //#else

    /*uint8_t channels[10] = {9,13,8,11,5,10,4,12,14,15};
    uint16_t* data = AnalogSensor::initialiserADC(10, channels);
    int nbSharp = 10;*/

    Sensors* sensors = Sensors::getSingleton();
    sharps = sensors->getSharpSensorsList();
    /*
    StrategieV2::sharps = new SharpSensor*;
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
    #endif*/
    emptySharpsToCheck();
    //@TODO
    /*enableSharp(SharpSensor::BACK_RIGHT);
    enableSharp(SharpSensor::FRONT_LEFT);*/
    /*enableSharp(SharpSensor::FRONT_LEFT);
    enableSharp(SharpSensor::FRONT_RIGHT);
    enableSharp(SharpSensor::FRONT_SIDE_LEFT);
    enableSharp(SharpSensor::FRONT_SIDE_RIGHT);

    enableSharp(SharpSensor::BACK_LEFT);
    enableSharp(SharpSensor::BACK_MIDDLE);
    enableSharp(SharpSensor::BACK_RIGHT);*/

#ifdef ROBOTHW
//        tourelle = new Tourelle(TIM6, 0);//TIM parameter is not implemented yet
    tourelle = new Tourelle();
    //tourelle->setZoneCritique(10, 27000);
#endif

    updateCount = 0;
}

StrategieV2::~StrategieV2()
{
    //dtor
}

long StrategieV2::getTimeSpent()
{
    return updateCount * 5;
}


void StrategieV2::update()
{
#ifndef ROBOTHW
    //qDebug() << timeToRestart;
#endif
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
        if (sharpsToCheck[i] && !tourneSurSoiMeme)
        {
            if (sharps[i]->getValue().b)
            {
                allume = true;
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
        }
        else
        {
            eteindreLED2();
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
                //currentCommand->collisionAvoided();
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

void StrategieV2::setCurrentGoal(Position goal, bool goBack, float maxSpeed, Angle precisionAngle)
{
    if (currentCommand != NULL)
        delete currentCommand;
//    if (actionsCount == 0)
//        currentCommand = new CommandAllerA(goal, goBack, maxSpeed/2);
//    else
    currentCommand = new CommandAllerA(goal, goBack, maxSpeed, 0.0f, precisionAngle);
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
}
void StrategieV2::setCurrentGoal(Position goal, Position center, float vitesse, bool goBack, Angle precisionAngle)
{
    if (currentCommand != NULL)
        delete currentCommand;
    currentCommand = new CommandAllerEnArcA(goal, center, vitesse*5, goBack);
    Asservissement::asservissement->setCommandSpeeds(currentCommand);
}
void StrategieV2::lookAt(Position pos, float maxSpeed)
{
    if (currentCommand != NULL)
        delete currentCommand;
    currentCommand = new CommandTournerVers(pos, maxSpeed); // create the command
    Asservissement::asservissement->setCommandSpeeds(currentCommand); // apply it
    StrategieV2::emptySharpsToCheck();
}
void StrategieV2::lookAt(Angle a, float maxSpeed)
{
    if (currentCommand != NULL)
        delete currentCommand;
    currentCommand = new CommandTournerVers(a, maxSpeed); // create the command
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
        enableSharp(SharpSensor::LEFT_FRONT);
        enableSharp(SharpSensor::RIGHT_FRONT);
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
        enableSharp(SharpSensor::LEFT_BACK);
        enableSharp(SharpSensor::RIGHT_BACK);
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

#ifndef ROBOTHW
SharpSensor** StrategieV2::getSensors()
{
    return sharps;
}

void StrategieV2::paint(QPainter* p)
{
    actionsToDo[actionsCount]->paint(p);
}

bool* StrategieV2::getSharpsToCheck()
{
    return sharpsToCheck;
}

#endif
