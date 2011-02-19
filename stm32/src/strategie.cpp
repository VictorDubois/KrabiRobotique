#include "strategie.h"
#include "odometrie.h"
#include "PositionPlusAngle.h"
#ifdef ROBOTHW
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#endif
#include "command.h"
#include <math.h>

#define INSTRUCTION_COLLISION 128

#ifndef NULL
#define NULL 0
#endif

Strategie* Strategie::strategie = NULL;

Strategie::Strategie(bool is_blue, Odometrie* odometrie) :
collision_detected(false)
{
    this->is_blue = is_blue;
    strategie = this;
#ifdef NOBODY //FIXME: Ce code est-il encore vraiment utile ?
    roueCodeuseDroite = new QuadratureCoderHandler(TIM2);
    roueCodeuseGauche = new QuadratureCoderHandler(TIM1);
#endif
    Position positionDeDepart(200,200);
    //Position positionDeDepart(1100,300);
    Angle angleDeDepart(0);

    positionDeDepart.y = positionDeDepart.y*(is_blue ? 1:-1);
    angleDeDepart = angleDeDepart*(is_blue ? 1:-1);
    //command = new Asservissement(PositionPlusAngle(Position(335, 400), Angle(M_PI_2)), roueCodeuseGauche, roueCodeuseDroite);
    odometrie->setPos(PositionPlusAngle(positionDeDepart,angleDeDepart));
    //command = new Asservissement(PositionPlusAngle(positionDeDepart, angleDeDepart), roueCodeuseGauche, roueCodeuseDroite);
    //command = new Asservissement(PositionPlusAngle(Position(0, 0), Angle(0)), roueCodeuseGauche, roueCodeuseDroite);
    //command->strategie = this;
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
    /*if(n == 1)
		(new TrapezoidalCommand)->goTo(Position(400, 400));
    return;*/
switch(n) {
	case 1:
		(new TrapezoidalCommand)->goTo(Position(600, 200));
	break;
	case 2:
		(new TrapezoidalCommand)->goTo(Position(900, 300));
	break;
	case 3:
		(new TrapezoidalCommand)->goTo(Position(1100, 700));
	break;
	case 4:
		(new TrapezoidalCommand)->goTo(Position(1150, 1000));
	break;
	case 5:
		(new TrapezoidalCommand)->goTo(Position(1325 + 100, 1535));
	break;
	case 6:
		(new TrapezoidalCommand)->goTo(Position(1325 + 100, 1725));
	break;
	case 7:
		(new TrapezoidalCommand)->goTo(Position(1325 + 100, 1525));
	break;
	default:
	break;
	}

//rouleau.recracheBoule();
//return;
#ifdef DONTUSE
    switch(n) {
        case 1:
	    command->goTo(Position(780, cote*780), false);
        break;
        case 2:
            rouleau.avaleBoule();
            command->goTo(Position(1840, cote*2640));
        break;
        case 3:
            command->goToDirection(Angle(0));
            break;
        case 4:
            rouleau.recracheBoule();
            break;
        /*case 3:
            //rouleau.recracheBoule();
            command->goTo(Position(400, 600));
        break;*/
        /*case 4:
            rouleau.arrete();
            command->goTo(Position(200, 800));
        break;
        case 5:
            command->goTo(Position(-200, 800));
        break;
        case 6:
            rouleau.recracheBoule();
            command->goTo(Position(-400, 600));
        break;
        case 7:
            rouleau.arrete();
            command->goTo(Position(-400, 200));
        break;
        case 8:
            command->goTo(Position(-200, 0));
        break;
        case 9:
            rouleau.arrete();
            command->goTo(Position(0, 0));
        break;*/
        default:
        break;
    }
    #endif

#if (0)
    switch(n) {
        case 1:
            //rouleau.avaleBoule();
            //command->tourne(Angle(1.5));
            command->goTo(Position(724, cote*779), false);
        break;
        case 2:
            //rouleau.avaleBoule();
            command->goTo(Position(1242, cote*1694), false);
        break;
        case 3:
            //rouleau.avaleBoule();
            command->goTo(Position(1790, cote*2610),false);
        break;
        case 4:
            command->goToDirection(Angle(0));
            break;
        case 5:
            //rouleau.recracheBoule();
            command->goTo(Position(1750, cote*2610));
            break;
        case 6:
            command->goTo(Position(1820, cote*2610));
            break;
        case INSTRUCTION_COLLISION:
            command->recule(Distance(100));
            break;
        case (INSTRUCTION_COLLISION+1):
            command->tourne(Angle(1.5));
            collision_detected = false;
            instruction_nb--;
        break;

    }
#endif
/*
if(n==0)
{
    command->recule(2500);
}*/
}

void Strategie::theEnd() { }
