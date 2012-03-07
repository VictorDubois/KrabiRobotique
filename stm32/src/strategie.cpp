#include "strategie.h"
#include "TrapezoidalCommand.h"
#include "CommandAvancerToutDroit.h"
#include "CommandTouner.h"
#include "CommandGoTo.h"



Strategie* Strategie::strategie = NULL;

Strategie::Strategie(bool is_blue, Odometrie* odometrie) :
collision_detected(false)
{
    this->is_blue = is_blue;
    this->odometrie = odometrie;
    strategie = this;
    Position positionDeDepart(POS_DEPART_X,POS_DEPART_Y);
    Angle angleDeDepart(0);

    positionDeDepart.setY(positionDeDepart.getY()*(is_blue ? 1:-1));
    angleDeDepart = angleDeDepart*(is_blue ? 1:-1);
    //command = new Asservissement(PositionPlusAngle(Position(335, 400), Angle(M_PI_2)), roueCodeuseGauche, roueCodeuseDroite);
    odometrie->setPos(PositionPlusAngle(positionDeDepart,angleDeDepart));
    //command = new Asservissement(PositionPlusAngle(positionDeDepart, angleDeDepart), roueCodeuseGauche, roueCodeuseDroite);
    //command = new Asservissement(PositionPlusAngle(Position(0, 0), Angle(0)), roueCodeuseGauche, roueCodeuseDroite);
    //command->strategie = this;
    instruction_nb=1;
    doNthInstruction(instruction_nb);
}

void Strategie::done(){
    //Si tout est ok, on passe à la suite
    if(!collision_detected){
        instruction_nb++;
        doNthInstruction(instruction_nb);
    }
    else{   //Sinon on fait les instructions au dessus de 128 (Pas utilisé ici)
        instruction_collision_nb++;
        doNthInstruction(INSTRUCTION_COLLISION+instruction_collision_nb);
    }

}

void Strategie::collisionDetected(){
    collision_detected = true;
    instruction_collision_nb=0;
    doNthInstruction(INSTRUCTION_COLLISION);
}


void Strategie::doNthInstruction(uint16_t n){
   int cote = (is_blue ? 1:-1);
  // CommandAvancerToutDroit* tmp = NULL;
  CommandGoTo* tmp = NULL;

    switch(n) {
       case 1:
              // (tmp = new CommandAvancerToutDroit(1000.));
               (tmp = new CommandGoTo(Position(800.,400.)));

        break;
     /*   case 2:
                delete tmp;
                (tmp = new TrapezoidalCommand)->goTo(Position(1000, cote*450),true);
        break;
        case 3:
                delete tmp;
               (tmp = new TrapezoidalCommand)->goTo(Position(1500, cote*275),true);
        break;
        case 4:
                delete tmp;
                (tmp = new TrapezoidalCommand)->goTo(Position(1300, cote*300),true);

        break;
        */
  /*      case 5:
          delete tmp;
               (tmp = new TrapezoidalCommand)->goTo(Position(2000, cote*500),true);
        break;
        case 6:
                delete tmp;
                (tmp = new TrapezoidalCommand)->goTo(Position(1000, cote*650),true);
        break;
        case 7:
                delete tmp;
                (tmp = new TrapezoidalCommand)->goTo(Position(400, cote*750),true);
                delete tmp;
        break;
        case 8:
                delete tmp;
                (tmp = new TrapezoidalCommand)->goTo(Position(650,cote*900),true);
        break;
*/
  /*    case 9:
          // delete tmp;
           //     (tmp = new TrapezoidalCommand)->goTo(Position(650,cote*1000),true);
        break;
<     /*   case 10:
            delete tmp;
                (tmp = new TrapezoidalCommand)->goTo(Position(1420,cote*1200),true);
        break;
        case 11:
                delete tmp;
                (tmp = new TrapezoidalCommand)->goTo(Position(1420,cote*1050),true);
        break;
   /*     case 12:
           delete tmp;
   //             (tmp = new TrapezoidalCommand)->goTo(Position(720,cote*1730),true);
        break;
        case 13:
                (tmp = new TrapezoidalCommand)->goTo(Position(1820,cote*680),true);
                delete tmp;
        break;
        case 14:
                (tmp = new TrapezoidalCommand)->goTo(Position(1980,cote*1450),true);
                delete tmp;
        break;
        case 15:
                (tmp = new TrapezoidalCommand)->goTo(Position(2050,cote*1700),true);
                delete tmp;
        break;
        case 16:
                (tmp = new TrapezoidalCommand)->goTo(Position(1000,cote*300),true);
                delete tmp;
        break;
        case 17:
                (tmp = new TrapezoidalCommand)->goTo(Position(1000,cote*1400),true);
                delete tmp;
       break;*/
      	default:
	break;



	}

}


