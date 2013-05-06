#include "strategie.h"
#include "odometrie.h"
#include "asservissement.h"
#include "commandAllerA.h"
#include "marteaux.h"
/*#include "CommandAvancerToutDroit.h"
#include "CommandTourner.h"
#include "Bras.h"
*/


Strategie* Strategie::strategie = NULL;

Strategie::Strategie(bool is_blue, Odometrie* odometrie)
    : collision_detected(false)//, listeActions(NULL)
{
    this->is_blue = is_blue;
    this->odometrie = odometrie;
    Strategie::strategie = this;
    instruction_nb = 0;

   /* Position positionDeDepart(POS_DEPART_X,POS_DEPART_Y);
    Angle angleDeDepart(ANGLE_DEPART);

     positionDeDepart.setY(is_blue ? positionDeDepart.getY() : -positionDeDepart.getY());

    angleDeDepart = (is_blue ? angleDeDepart : -angleDeDepart);
*/
    //command = new Asservissement(PositionPlusAngle(Position(335, 400), Angle(M_PI_2)), roueCodeuseGauche, roueCodeuseDroite);

//Position posDepart(00.0f, -500.0f);
    Position posDepart(270.0f, 400.0f);
    Angle angleDepart = 0;
    PositionPlusAngle depart(posDepart, angleDepart);
    odometrie->setPos(depart);

    //command = new Asservissement(PositionPlusAngle(positionDeDepart, angleDeDepart), roueCodeuseGauche, roueCodeuseDroite);
    //command = new Asservissement(PositionPlusAngle(Position(0, 0), Angle(0)), roueCodeuseGauche, roueCodeuseDroite);
    //command->strategie = this;
 //   instruction_nb=1;
  //  doNthInstruction(instruction_nb);
  /* listeActions= new ListeActions(odometrie,is_blue);

    listeActions->creerPremiereAction();*/

    Position posTest(1600.0f, 400.0f);
    Position centre(0.0f, 0.0f);
    commande = new CommandAllerA(posTest, false);
   // commande = new CommandAllerEnArcA(posTest, centre, 1.0f, false);
    instruction_nb = 0;
}

struct PosBougie
{
    Position pos;
    Position lookAt;
    bool haut;
};

void Strategie::update()
{

    static const int nbBougies = 18;
    static PosBougie tabPosBougie[nbBougies] =
    {
        {Position(2160.0, 1810.0), Position(1860.0, 0.0), true},
        {Position(2154.0, 1779.0), Position(1740.0, 0.0), false},
        {Position(2095.0, 1630.0), Position(1300.0, 0.0), false},
        {Position(2069.0, 1576.0), Position(1120.0, 0.0), true},
        {Position(1989.0, 1467.0), Position(680.0, 0.0), false},
        {Position(1903.0, 1383.0), Position(270.0, 0.0), true},
        {Position(1837.0, 1338.0), Position(0.0, 280.0), false},
        {Position(1704.0, 1272.0), Position(0.0, 520.0), false},
        {Position(1629.0, 1250.0), Position(0.0, 1080.0), true},
        {Position(1525.0, 1227.0), Position(0.0, 1220.0), false},
        {Position(1381.0, 1252.0), Position(0.0, 1650.0), true},
        {Position(1335.0, 1312.0), Position(0.0, 1640.0), false},
        {Position(1162.0, 1384.0), Position(190.0, 2000.0), false},
        {Position(1113.0, 1420.0), Position(440.0, 2000.0), true},
        {Position(1026.0, 1500.0), Position(560.0, 2000.0), false},
        {Position(951.0, 1585.0), Position(640.0, 2000.0), true},
        {Position(913.0, 1640.0), Position(700.0, 2000.0), false},
        {Position(850.0, 1756.0), Position(740.0, 2000.0), false}
    };


    static int etatBougie = 0;
    switch (instruction_nb)
    {
        case 0:
        {
            if (commande->fini())//diff.getNorme() < 20)
            {
                instruction_nb++;
                Position posBut(tabPosBougie[0].pos.x, 1000.0f);
                delete commande;
                commande = new CommandAllerA(posBut, false);
            }
        }
        break;

        case 1:
        {
            if (commande->fini())
            {
                instruction_nb++;
                etatBougie = 1;
                delete commande;
                commande = new CommandAllerA(tabPosBougie[0].pos, true);
                Marteaux::releverHautDroit();
                Marteaux::releverBasDroit();
            }
        }
        break;

        default:

            if (instruction_nb <= 12)
            {
                switch (etatBougie)
                {
                    case 0:
                        if (commande->fini())
                        {
                            etatBougie++;
                            delete commande;
                            commande = new CommandAllerA(tabPosBougie[instruction_nb-2].pos, false);
                        }
                        break;
                    case 1:
                        if (commande->fini())
                        {
                            etatBougie++;
                            delete commande;
                            commande = new CommandTournerVers(tabPosBougie[instruction_nb-2].lookAt);
                        }
                        break;
                    case 2:
                        if (commande->fini())
                        {
                            etatBougie++;
                            delete commande;
                            commande = new CommandAttendre(200);
                        }
                        break;
                    case 3:
                        if (commande->fini())
                        {
                            etatBougie++;
                            delete commande;
                            commande = new CommandAttendre(100);
                            if (tabPosBougie[instruction_nb-2].haut)
                                Marteaux::enfoncerHautDroit();
                            else
                                Marteaux::enfoncerBasDroit();
                        }
                        break;
                    case 4:
                        if (commande->fini())
                        {
                            etatBougie = 0;
                            delete commande;
                            commande = new CommandAttendre(200);
                            if (tabPosBougie[instruction_nb-2].haut)
                                Marteaux::releverHautDroit();
                            else
                                Marteaux::releverBasDroit();
                            instruction_nb++;
                        }
                        break;
                }
                break;
            }

            Asservissement::asservissement->setAngularSpeed(0.0f);
            Asservissement::asservissement->setLinearSpeed(0.0f);
            instruction_nb++;
            return;
    }

/*
    Position centre(0.0f, 0.0f);
    switch (instruction_nb)
    {
        case 0:
        {
            Position pos(0.0f, -500.0f);
            Position diff = Odometrie::odometrie->getPos().getPosition() - pos;
            if (diff.getNorme() < 40)
            {
                instruction_nb++;
                Position posBut(500.0f, 0.0f);
                delete commande;
                commande = new CommandAllerEnArcA(posBut, centre, 2.0f, false);
            }
        }
        break;

        case 1:
        {
            Position pos(500.0f, 0.0f);
            Position diff = Odometrie::odometrie->getPos().getPosition() - pos;
            if (diff.getNorme() < 40)
            {
                instruction_nb++;
                Position posBut(0.0f, 500.0f);
                delete commande;
                commande = new CommandAllerEnArcA(posBut, centre, 2.0f, false);
            }
        }
        break;

        case 2:
        {
            Position pos(0.0f, 500.0f);
            Position diff = Odometrie::odometrie->getPos().getPosition() - pos;
            if (diff.getNorme() < 40)
            {
                instruction_nb++;
                Position posBut(-500.0f, 0.0f);
                delete commande;
                commande = new CommandAllerEnArcA(posBut, centre, 2.0f, false);
            }
        }
        break;

        case 3:
        {
            Position pos(-500.0f, 0.0f);
            Position diff = Odometrie::odometrie->getPos().getPosition() - pos;
            if (diff.getNorme() < 40)
            {
                instruction_nb= 0;
                Position posBut(0.0f, -500.0f);
                delete commande;
                commande = new CommandAllerEnArcA(posBut, centre, 2.0f, false);
            }
        }
        break;

        default:
            Asservissement::asservissement->setAngularSpeed(0.0f);
            Asservissement::asservissement->setLinearSpeed(0.0f);
            return;
    }
*/

 /*   switch (instruction_nb)
    {
        case 0:
        {
            instruction_nb++;
            Position posBut(2400.0f, 300.0f);
            delete commande;
            commande = new CommandAllerA(posBut, false);
        }
        break;

        case 1:
        {
            Position pos(2400.0f, 300.0f);
            Position diff = Odometrie::odometrie->getPos().getPosition() - pos;
            if (diff.getNorme() < 10)
            {
                instruction_nb++;
                Position posBut(2400.0f, 550.0f);
                delete commande;
                commande = new CommandAllerA(posBut, true);
            }
        }
        break;

        case 2:
        {
            Position pos(2400.0f, 550.0f);
            Position diff = Odometrie::odometrie->getPos().getPosition() - pos;
            if (diff.getNorme() < 10)
            {
                instruction_nb++;
                Position posBut(500.0f, 550.0f);
                delete commande;
                commande = new CommandAllerA(posBut, false);
            }
        }
        break;

        case 3:
        {
            Position pos(500.0f, 550.0f);
            Position diff = Odometrie::odometrie->getPos().getPosition() - pos;
            if (diff.getNorme() < 10)
            {
                instruction_nb++;
            }
        }
        break;

        default:
            Asservissement::asservissement->setAngularSpeed(0.0f);
            Asservissement::asservissement->setLinearSpeed(0.0f);
            return;
    }
*/
/*
if (commande != NULL)
    delete commande;
commande = new CommandTestTournerGauche();
commande = new CommandTestAvancer();
*/
if (commande != NULL)
 commande->update();
   Asservissement::asservissement->setCommandSpeeds(commande);

}


