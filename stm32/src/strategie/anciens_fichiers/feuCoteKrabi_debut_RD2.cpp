#include "feuCoteKrabi.h"
#include "strategieV2.h"
#include "command.h"

FeuCoteKrabi::FeuCoteKrabi(){}

FeuCoteKrabi::FeuCoteKrabi(bool isBlue, Position positionDepart, int type, float precision)
{
    this->isBlue = isBlue;
    this->positionDepart = positionDepart;
    this->type = type;
    this->precision = precision;
    this->bracquemart = Brak::getSingleton();
    if (type == 0)
        this->positionChopperFeu = Position(250, 1200, isBlue);
    else if (type == 1)
        this->positionChopperFeu = Position(1300, 250, isBlue);
    else if (type == 2)
        this->positionChopperFeu = Position(1700, 250, isBlue);
    else
        this->positionChopperFeu = Position(2750, 1200, isBlue);
}

int FeuCoteKrabi::update()
{
    if (status == 0)
    {
        status = 1;
    }
    else if (status == 1)
    {
        StrategieV2::setCurrentGoal(positionDepart, false);//, 1.0f);
        status++;
    }
    else if (status == 2)
    {
        if (Command::isNear(positionDepart))
        {
            status++;
        }
    }
    else if (status == 3 && (type%2 == 0))
    {
        StrategieV2::setCurrentGoal(positionChopperFeu, false, 1.0f);
        status++;
    }
    else if (status == 3)
    {
        StrategieV2::lookAt(positionChopperFeu);
        status = 152;
    }
    else if (status == 4)
    {
        if (Command::isNear(positionChopperFeu))
        {
            StrategieV2::lookAt(Position(type==0 ? 0 : 1700, type==0 ? 1200 : 250, isBlue));
            status++;
        }
    }
    else if (status == 5)
    {
        if (Command::isLookingAt(Position(type==0 ? 0 : 1700, type==0 ? 1200 : 250, isBlue)))
        {
            bracquemart->positionFeuHautTorche();
            status++;
        }
    }
    else if (status < 150)
    {
        status++;
    }
    else if (status == 150)
    {
        StrategieV2::setCurrentGoal(positionDepart, true, 1.0f);
        status++;
    }
    else if (status == 151)
    {
        if (Command::isNear(positionDepart))
        {
            bracquemart->positionHaute();
            status = -1;
        }
    }
    else if (status == 152) // autre type de feu
    {
        if(Command::isLookingAt(positionChopperFeu))
        {
            bracquemart->positionFeuHautTorche();
            status++;
        }
    }
    else if (status < 202)
    {
        StrategieV2::setCurrentGoal(positionChopperFeu, false, 0.7);
        status++;
    }
    else if (status == 202)
    {
        if (Command::isNear(positionChopperFeu))
        {
            StrategieV2::lookAt(Position(type==1 ? 1300 : 3000, type==1 ? 0 : 1200, isBlue));
            status++;
        }
    }
    else if (status < 252)
    {
        status++;
    }
    else if (status == 252)
    {
        if (Command::isLookingAt(Position(type==1 ? 1300 : 3000, type==1 ? 0 : 1200, isBlue)))
        {
            bracquemart->attraperFeu();
            status++;
        }
    }
    else if (status < 303)
    {
        status++;
    }
    else if (status == 303)
    {
        StrategieV2::setCurrentGoal(positionDepart, true, 1.0);
        status++;
    }
    else if (status == 304)
    {
        if (Command::isNear(positionDepart))
        {
            bracquemart->relacherFeu();
            status++;
        }
    }
    else if (status < 354)
    {
        status++;
    }
    else if (status == 354)
    {
        bracquemart->positionHaute();
        status = -1;
    }

    return status;
}
