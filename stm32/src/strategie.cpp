#include "strategie.h"
#include "CommandGoTo.h"


Strategie* Strategie::strategie = NULL;

Strategie::Strategie(bool is_blue, Odometrie* odometrie) :
collision_detected(false), listeActions(NULL)
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
    listeActions= new ListeDActions(odometrie);
    listeActions->creerPremiereAction();
}

void Strategie::update(){

  if(listeActions->getActionActuelle()->executer())
    {
        listeActions->supprimerPremiereAction();
        listeActions->creerPremiereAction();
    }

/*    if (instruction_nb != 0)
    {
        new CommandGoTo(Position(500,0));
        instruction_nb = 0;
    }
*/
   /* //Si tout est ok, on passe à la suite
    if(!collision_detected){
        instruction_nb++;
        doNthInstruction(instruction_nb);
    }
    else{   //Sinon on fait les instructions au dessus de 128 (Pas utilisé ici)
        instruction_collision_nb++;
        doNthInstruction(INSTRUCTION_COLLISION+instruction_collision_nb);
    }
*/
}

void Strategie::collisionDetected(){
    collision_detected = true;
    instruction_collision_nb=0;
    doNthInstruction(INSTRUCTION_COLLISION);
}


void Strategie::doNthInstruction(uint16_t n){
   int cote = (is_blue ? 1:-1);
}


