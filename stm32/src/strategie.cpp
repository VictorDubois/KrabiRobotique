#include "strategie.h"
#include "CommandGoTo.h"
#include "CommandAvancerToutDroit.h"
#include "CommandTourner.h"
#include "ListeDActions.h"




Strategie* Strategie::strategie = NULL;

Strategie::Strategie(bool is_blue, Odometrie* odometrie) :
collision_detected(false)//, listeActions(NULL)
{
    this->is_blue = is_blue;
    this->odometrie = odometrie;
    Strategie::strategie = this;
    Position positionDeDepart(POS_DEPART_X,POS_DEPART_Y);
    Angle angleDeDepart(0);

    positionDeDepart.setY(positionDeDepart.getY()*(is_blue ? 1:-1));
    angleDeDepart = angleDeDepart*(is_blue ? 1:-1);
    //command = new Asservissement(PositionPlusAngle(Position(335, 400), Angle(M_PI_2)), roueCodeuseGauche, roueCodeuseDroite);
    odometrie->setPos(PositionPlusAngle(positionDeDepart,angleDeDepart));
    //command = new Asservissement(PositionPlusAngle(positionDeDepart, angleDeDepart), roueCodeuseGauche, roueCodeuseDroite);
    //command = new Asservissement(PositionPlusAngle(Position(0, 0), Angle(0)), roueCodeuseGauche, roueCodeuseDroite);
    //command->strategie = this;
 /*   instruction_nb=1;
    doNthInstruction(instruction_nb); */
    listeActions= new ListeDActions(odometrie,is_blue);
    listeActions->creerPremiereAction();

}

void Strategie::update(){
    int cote = (is_blue ? 1:-1);

if (listeActions->getActionActuelle())
{
    if(listeActions->getActionActuelle()->executer())
    {
        Command::freinageDUrgence(true);
        listeActions->supprimerPremiereAction();
        listeActions->creerPremiereAction();
    }
}
/*
   bool dejaVu = false;
   if (Asservissement::asservissement->command == NULL)
    {
        new CommandGoTo(Position(1000,cote*400));
     //   int i =0; i++;
    // new CommandTourner(Angle(M_PI_2));
    //    new CommandAvancerToutDroit(1000);
    }
    int d = (odometrie->getPos().getPosition()-Position(1000,cote*400)).getNorme();
    if ((odometrie->getPos().getPosition()-Position(1000,cote*400)).getNorme()< 300 && !dejaVu)
    {
        dejaVu = true;
        new CommandGoTo(Position(1000,cote*1000));
    }
   if ((odometrie->getPos().getPosition()-Position(1000,cote*1000)).getNorme()< 300)
    {
        Command::freinageDUrgence(true);
    }
*/   /* //Si tout est ok, on passe à la suite
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

}


