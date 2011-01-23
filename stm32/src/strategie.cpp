#include "strategie.h"
#include "PositionPlusAngle.h"
#ifdef ROBOTHW
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#endif
#include "asservissement.h"
#include <math.h>

#define INSTRUCTION_COLLISION 128

Strategie::Strategie(bool is_blue, Asservissement* asservissement) :
collision_detected(false)
{
    this->is_blue = is_blue;
#ifdef NOBODY
    roueCodeuseDroite = new QuadratureCoderHandler(TIM2);
    roueCodeuseGauche = new QuadratureCoderHandler(TIM1);
#endif
    //Position positionDeDepart(335,400);
    //Angle angleDeDepart(M_PI_2);
    //Position positionDeDepart(255,275);
    //Angle angleDeDepart(0.779);
    Position positionDeDepart(0,0);
    Angle angleDeDepart(0);

    positionDeDepart.y = positionDeDepart.y*(is_blue ? 1:-1);
    angleDeDepart = angleDeDepart*(is_blue ? 1:-1);
    //asservissement = new Asservissement(PositionPlusAngle(Position(335, 400), Angle(M_PI_2)), roueCodeuseGauche, roueCodeuseDroite);
    this->asservissement = asservissement;
    asservissement->odometrie->setPos(PositionPlusAngle(positionDeDepart,angleDeDepart));
    //asservissement = new Asservissement(PositionPlusAngle(positionDeDepart, angleDeDepart), roueCodeuseGauche, roueCodeuseDroite);
    //asservissement = new Asservissement(PositionPlusAngle(Position(0, 0), Angle(0)), roueCodeuseGauche, roueCodeuseDroite);
    asservissement->strategie = this;
    instruction_nb=1;
    doNthInstruction(instruction_nb);
}

void Strategie::doNext(){
}

void Strategie::foundOtherRobot(){
}
void Strategie::done(){
    if(!collision_detected){
        instruction_nb++;
        doNthInstruction(instruction_nb);
    }
    else{
        instruction_collision_nb++;
        doNthInstruction(INSTRUCTION_COLLISION+instruction_collision_nb);
    }

}

void Strategie::collisionDetected() {
    collision_detected = true;
    instruction_collision_nb=0;
    doNthInstruction(INSTRUCTION_COLLISION);
}

void Strategie::doNthInstruction(uint16_t n){
    int cote = (is_blue ? 1:-1);

    if(n==1)
        asservissement->goTo(Position(100, 100), false);
    return;
//rouleau.recracheBoule();
//return;
#ifdef DONTUSE
    switch(n) {
        case 1:
            asservissement->goTo(Position(780, cote*780), false);
        break;
        case 2:
            rouleau.avaleBoule();
            asservissement->goTo(Position(1840, cote*2640));
        break;
        case 3:
            asservissement->goToDirection(Angle(0));
            break;
        case 4:
            rouleau.recracheBoule();
            break;
        /*case 3:
            //rouleau.recracheBoule();
            asservissement->goTo(Position(400, 600));
        break;*/
        /*case 4:
            rouleau.arrete();
            asservissement->goTo(Position(200, 800));
        break;
        case 5:
            asservissement->goTo(Position(-200, 800));
        break;
        case 6:
            rouleau.recracheBoule();
            asservissement->goTo(Position(-400, 600));
        break;
        case 7:
            rouleau.arrete();
            asservissement->goTo(Position(-400, 200));
        break;
        case 8:
            asservissement->goTo(Position(-200, 0));
        break;
        case 9:
            rouleau.arrete();
            asservissement->goTo(Position(0, 0));
        break;*/
        default:
        break;
    }
    #endif

    switch(n) {
        case 1:
            //rouleau.avaleBoule();
            //asservissement->tourne(Angle(1.5));
            asservissement->goTo(Position(724, cote*779), false);
        break;
        case 2:
            //rouleau.avaleBoule();
            asservissement->goTo(Position(1242, cote*1694), false);
        break;
        case 3:
            //rouleau.avaleBoule();
            asservissement->goTo(Position(1790, cote*2610),false);
        break;
        case 4:
            asservissement->goToDirection(Angle(0));
            break;
        case 5:
            //rouleau.recracheBoule();
            asservissement->goTo(Position(1750, cote*2610));
            break;
        case 6:
            asservissement->goTo(Position(1820, cote*2610));
            break;
        case INSTRUCTION_COLLISION:
            asservissement->recule(Distance(100));
            break;
        case (INSTRUCTION_COLLISION+1):
            asservissement->tourne(Angle(1.5));
            collision_detected = false;
            instruction_nb--;
        break;

    }
/*
if(n==0)
{
    asservissement->recule(2500);
}*/
}

void Strategie::theEnd() { }
