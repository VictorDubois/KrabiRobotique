#include "actionGoTo.h"
#include "odometrie.h"
#include "strategieV2.h"

ActionGoTo::ActionGoTo(Position goalPos, bool goBack1) : MediumLevelAction(goalPos)
{
    goBack = goBack1;
    goalAngle = 0;
    goingCurve = false;
    curveFactor = 1;
}

ActionGoTo::~ActionGoTo()
{
    //dtor
}

int ActionGoTo::update()
{
    if (status == 0)
    {
        Position pos = Odometrie::odometrie->getPos().getPosition();
        Position vect = goalPosition - pos;
        vect /= vect.getNorme();

        goingCurve = StrategieV2::getJustAvoided();

        if (goingCurve)
        {
            StrategieV2::setCurrentGoal(Odometrie::odometrie->getPos().getPosition(), false); // a changer selon le servo qui détecte
            status = 1;
        }
        else
        {
            StrategieV2::setCurrentGoal(goalPosition, goBack);
            status = 3;
        }

    }
    else if (status ==1) // on recule
    {
        Position vect = goalPosition - Odometrie::odometrie->getPos().getPosition();
        if (true)//(vect.getNorme() < 100.0) // now we have
        {
            Position pos = Odometrie::odometrie->getPos().getPosition();
            Position vect = goalPosition - pos;
            float distance = vect.getNorme();
            vect /= distance;
            curveFactor = distance/50;
            goalAngle = wrapAngle(M_PI*10.f/(float)(curveFactor)+vect.getAngle());
            StrategieV2::lookAt(pos+Position(100*cos(goalAngle),100*sin(goalAngle)));
            status = 2;
        }
    }
    else if (status == 2)
    {
        //std::cout << "status = 2" << std::endl;
        float currentAngle = wrapAngle(Odometrie::odometrie->getPos().getAngle());
        if (fabs(currentAngle - goalAngle) < 0.02)
        {
            if (goingCurve)
            {
                Position currentPos = Odometrie::odometrie->getPos().getPosition();
                Position moitie = (goalPosition-currentPos);
                moitie /= 2;
                Position vect = moitie;
                vect /= vect.getNorme();
                //std::cout << vect.getX() << " " << vect.getY() << std::endl;

                moitie += Position(curveFactor*20*vect.getY(),curveFactor*(-20)*vect.getX()); // on déplace le point pour qu'il soit décalé du milieu

                StrategieV2::setCurrentGoal(goalPosition, currentPos + moitie, 1, false);
                StrategieV2::setJustAvoided(false);
                status = 3;
            }
            else
            {
                StrategieV2::setCurrentGoal(goalPosition, goBack);
                status = 3;
            }
        }
    }
    else if (status == 3)
    {
        //std::cout << "status = 3" << std::endl;
        Position vect = goalPosition - Odometrie::odometrie->getPos().getPosition();
        //std::cout << vect.getNorme() << std::endl;
        //std::cout << Odometrie::odometrie->getPos().getPosition().getX() << " "<< Odometrie::odometrie->getPos().getPosition().getY()   << std::endl;
        if (vect.getNorme() < 10.0)
            status = -1;
    }
    return status;
}

void ActionGoTo::collisionAvoided()
{
    //if (status > 0)
        this->status = 0;
}
