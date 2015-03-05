#include "fresque.h"
#include "strategieV2.h"
#include "actionGoTo.h"
#include "leds.h"
#include "odometrie.h"
#include "asservissement.h"
#include "actionGoTo.h"
#include "sharpSensor.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

Fresque::Fresque(){}

Fresque::Fresque(bool isBlue, Position positionDepart, Position positionFin, float precision) : MediumLevelAction()
{
    this->isBlue = isBlue;
    this->positionDepart = positionDepart;
    this->positionFin = positionFin;
    this->precision = precision;
    this->positionIntermediaire = Position(this->positionDepart.getX(), this->positionDepart.getY());//(this->positionDepart.getY()*5+2000)/6);
    this->tempsColleALaFresque = 300;
    this->tempsRecule = 50;
    status = 0;
    sensor = Sensors::getSingleton();
}

Fresque::~Fresque()
{
    //dtor
}

int Fresque::update()
{
    if (status == 0)
    {
#ifndef ROBOTHW
        qDebug() << "fresque";
#endif
        status++;
    }

    else if (status == 1) // mise en place du robot
    {
#ifndef ROBOTHW
        qDebug() << "fresque 1";
#endif
        StrategieV2::setCurrentGoal(positionDepart, false);
        sensor->desactiveSharp(SharpSensor::FRONT_LEFT);
        sensor->desactiveSharp(SharpSensor::FRONT_RIGHT);
        sensor->desactiveSharp(SharpSensor::LEFT_FRONT);
        sensor->desactiveSharp(SharpSensor::RIGHT_FRONT);
        status++;
    }
    else if (status == 2) // mise en place du robot
    {
        if(Command::isNear(positionDepart))
        {
            StrategieV2::lookAt(M_PI/2.);

            status++;
        }
    }
    else if (status == 3) // mise en place du robot
    {
        if(Command::isLookingAt(M_PI/2., DEGTORAD(360.)))
        {
            Asservissement::asservissement->setEnabledPIDAngle(false);
            Asservissement::asservissement->setLinearDuty(0.2);

            status++;
        }
    }
    else if(status < tempsColleALaFresque)//On attend pendant (tempsColleALaFresque) * 5ms, le temps que le robot se colle à la fresque
    {
        status++;
    }
    /*else if (status == tempsColleALaFresque)
    {
        //Asservissement::asservissement->setEnabledPIDAngle(true);
        //Asservissement::asservissement->setLinearDuty(-0.3);

        qDebug() << status;
        status++;
    }
    else if(status < tempsColleALaFresque+tempsRecule)
    {
        qDebug() << status;
        status++;
    }*/
    else if (status == tempsColleALaFresque/*+tempsRecule*/)
    {
        //Asservissement::asservissement->resetFixedDuty();
        Asservissement::asservissement->setEnabledPIDDistance(true);
        StrategieV2::setCurrentGoal(positionFin, true);
        sensor->activeAllSharp();
        status++;
    }
    else if (status == tempsColleALaFresque/*+tempsRecule*/+1)
    {
        if(Command::isNear(positionFin))
            status = -1;
    }

    return status;
}
