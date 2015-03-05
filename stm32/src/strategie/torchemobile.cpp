#include "torchemobile.h"
//#include "tireLances.h"
#include "strategieV2.h"
#include "actionGoTo.h"
#include "leds.h"
#include "odometrie.h"
#include "asservissement.h"
#include "positionPlusAngle.h"

TorcheMobile::TorcheMobile() {}

TorcheMobile::TorcheMobile(bool isBlue, Position positionDepart, Position positionTorche, bool opponentSide, float precision)
{
    this->isBlue = isBlue;
    this->positionDepart = positionDepart;
    this->positionTorche = positionTorche;
    this->precision = precision;
    this->opponentSide = opponentSide;
    status = 0;
    bracquemart = Brak::getSingleton();
}

int TorcheMobile::update()
{
    if (status == 0)
    {
        status = 1;
    }
    else if (status == 1)
    {
        StrategieV2::setCurrentGoal(positionDepart, false, 1);
        status++;
    }
    else if (status == 2)
    {
        if (Command::isNear(positionDepart))
        {
            StrategieV2::lookAt(positionTorche);
            status++;
        }
    }
   else if (status == 3)
   {
       if (Command::isLookingAt(positionTorche))
       {
           bracquemart->positionFeuHautTorche();
           bracquemart->attraperFeu();
           status++;
       }
   }
   else if (status < 53)
   {
       status++;
   }
   else if (status == 53)
   {
       angle = Odometrie::odometrie->getPos().getAngle() - M_PI/5;
       StrategieV2::lookAt(angle);
       status++;
   }
   else if (status == 54)
   {
       if (Command::isLookingAt(angle))
       {
           bracquemart->relacherFeu();
           status++;
       }
   }
   else if (status < 104)
   {
       status++;
   }
   else if (status == 104)
   {
       bracquemart->positionIntermediaire();
       StrategieV2::lookAt(positionTorche);
       status++;
   }
   else if (status == 105)
   {
       if (Command::isLookingAt(positionTorche))
       {
            bracquemart->positionFeuMilieuTorche();
            bracquemart->attraperFeu();
            status++;
       }
   }
   else if (status < 205)
   {
       status++;
   }
   else if (status == 205)
   {
       bracquemart->positionIntermediaire();
       status++;
   }
   else if (status < 320)
   {
       status++;
   }
   else if (status == 320)
   {
       angle = Odometrie::odometrie->getPos().getAngle() - M_PI*0.9;
       StrategieV2::lookAt(angle);
       status++;
   }
   else if (status < 456)
   {
       status++;
   }
   else if (status == 456)
   {
       bracquemart->orienterHaut();
       status++;
   }
   else if (status < 556)
   {
       status++;
   }
   else if (status == 556)
   {
       bracquemart->positionBasseRetourne();
       status++;
   }
   else if (status < 756)
   {
       status++;
   }
   else if (status == 756)
   {
       bracquemart->relacherFeu();
       status++;
   }
   else if (status < 806)
   {
       status++;
   }
   else if (status == 806)
   {
       angle = angle - M_PI/6;
       StrategieV2::lookAt(angle);
       status++;
   }
   else if (status == 807)
   {
       if (Command::isLookingAt(angle))
       {
           bracquemart->positionIntermediaire();
           status++;
       }
   }
   else if (status < 907)
   {
       status++;
   }
   else if (status == 907)
   {
       bracquemart->orienterBas();
       status++;
   }
   else if (status < 1007)
   {
       status++;
   }
   else if (status == 1007)
   {
       StrategieV2::lookAt(positionTorche);
       status++;
   }
   else if (status == 1008)
   {
       if (Command::isLookingAt(positionTorche))
       {
           bracquemart->positionFeuBasTorche();
           bracquemart->attraperFeu();
           status++;
       }
   }
   else if (status < 1058)
   {
       status++;
   }
   else if (status == 1108)
   {
       bracquemart->positionIntermediaire();
       status++;
   }
   else if (status < 1158)
   {
       status++;
   }
   else if (status == 1158)
   {
       angle = Odometrie::odometrie->getPos().getAngle() + M_PI/3;
       StrategieV2::lookAt(angle);
       status++;
   }
   else if (status == 1159)
   {
       if (Command::isLookingAt(angle))
       {
           bracquemart->positionFeuMilieuTorche();
           status++;
       }
   }
   else if (status < 1209)
   {
       status++;
   }
   else if (status == 1209)
   {
       bracquemart->relacherFeu();
       status++;
   }
   else if (status < 1309)
   {
       status++;
   }
   else if (status == 1309)
   {
       bracquemart->positionHaute();
       status = -1;
   }

   return status;
}
