#include "actionSuivreChemin.h"
#include "sensors.h"
#include "command.h"
#include "strategie.h"
#include "bras.h"

#include <math.h>

ActionSuivreChemin::ActionSuivreChemin(ActionBase* tab, int n, Odometrie* odo)
:   chemin(NULL), taille(n), pointSuivant(0), odometrie(odo), faitquelquechose(false)
{
    if (n != 0)
        chemin = new ActionBase[n];

    for(int i = 0; i < n; i++)
        chemin[i] = tab[i];

    positionRobotAdverseUn = new Position();
    positionRobotAdverseDeux = new Position();
    positionRobotAdverseTrois  = new Position();
}

ActionSuivreChemin::~ActionSuivreChemin()
{
    if (chemin != NULL)
        delete[] chemin;
    delete positionRobotAdverseUn;
    delete positionRobotAdverseDeux;
    delete positionRobotAdverseTrois;
}

const Distance gaucheTotem = 975-RAYON_ROBOT;
const Distance droiteTotem = 2025+RAYON_ROBOT;
const Distance hautTotem = 1125+RAYON_ROBOT;
const Distance basTotem = 875-RAYON_ROBOT;

const Distance basTable = 0+RAYON_ROBOT;
const Distance hautTable = 2000-RAYON_ROBOT;
const Distance gaucheTable = 0+RAYON_ROBOT;
const Distance droiteTable = 3000-RAYON_ROBOT;

const Distance hautZoneDeDepart = 500+RAYON_ROBOT;
const Distance zoneDeDepartRouge = 500+RAYON_ROBOT;
const Distance zoneDeDepartBleu = 2500-RAYON_ROBOT;

const Distance BasZoneCapitaine = 1260-RAYON_ROBOT;
const Distance zoneCapitaineRouge = 400+RAYON_ROBOT;
const Distance zoneCapitaineBleu = 2600+RAYON_ROBOT;

bool ActionSuivreChemin::eviterDecoreEtRobot(Position pos,Position* posRobotAdverseUn,Position* posRobotAdverseDeux,Position* posRobotAdverseTrois)
{
    bool toucher = false;
    toucher |= (pos.x<droiteTotem) && (pos.x>gaucheTotem) && (pos.y<hautTotem) && (pos.y>basTotem);
    toucher |= (pos.y<basTable) && (pos.y>hautTable) && (pos.x<gaucheTable) && (pos.x>droiteTable);
    toucher |= (pos.y>BasZoneCapitaine) && ((pos.x<zoneCapitaineRouge) || (pos.x>zoneCapitaineBleu));
    toucher |= (pos.y<hautZoneDeDepart) && ((pos.x<zoneDeDepartRouge) || (pos.x>zoneDeDepartBleu));
    toucher |= ((pos.x - (posRobotAdverseUn->x))*(pos.x - (posRobotAdverseUn->x)) + (pos.y - (posRobotAdverseUn->y))*(pos.y - (posRobotAdverseUn->y))<RAYON_ROBOT);
    toucher |= ((pos.x - (posRobotAdverseDeux->x))*(pos.x - (posRobotAdverseDeux->x)) + (pos.y - (posRobotAdverseDeux->y))*(pos.y - (posRobotAdverseDeux->y))<RAYON_ROBOT);
    toucher |= ((pos.x - (posRobotAdverseTrois->x))*(pos.x - (posRobotAdverseTrois->x)) + (pos.y - (posRobotAdverseTrois->y))*(pos.y - (posRobotAdverseTrois->y))<RAYON_ROBOT);
    return toucher;
}

bool ActionSuivreChemin::trajetPossible(Position objectif,Position* posRobotAdverseUn,Position* posRobotAdverseDeux,Position* posRobotAdverseTrois)
{
    bool toucher=false;
    PositionPlusAngle** CheminTheorique = CommandGoTo::path(objectif);
    for(int i=0;i<PATH_LENGTH;i+=5)
    {
        Position pos=CheminTheorique[i]->getPosition();
        toucher |= eviterDecoreEtRobot(pos,positionRobotAdverseUn,
                                       positionRobotAdverseDeux,positionRobotAdverseTrois);
    }
    return !toucher;
}

int ActionSuivreChemin::intOfSensors()
{
    int nbCapteursActif=0;
    if(Sensors::getSensors()->detectedSharp(SharpSensor::FRONT_RIGTH)) nbCapteursActif +=10;
    if(Sensors::getSensors()->detectedSharp(SharpSensor::FRONT_LEFT)) nbCapteursActif +=20;
    if(Sensors::getSensors()->detectedSharp(SharpSensor::RIGTH)) nbCapteursActif +=1;
    if(Sensors::getSensors()->detectedSharp(SharpSensor::LEFT)) nbCapteursActif +=2;
   // if(Sensors::getSensors()->detectedSharp(SharpSensor::BACK)) nbCapteursActif +=100;
    if(Sensors::getSensors()->detectedSharp(SharpSensor::FRONT)) nbCapteursActif +=40;

    return Sensors::getSensors()->detectedSharp()->getSize(); //nbCapteursActif;
}

void ActionSuivreChemin::affectePosRobotAdverse(int capteursOuverts, int cote)
{
    Angle angle = odometrie->getPos().getAngle();
    Position VectUn;
    Position VectDeux;
    Position VectTrois;
    switch(capteursOuverts)
    {
    case 1:
            VectUn=Position((RAYON_ROBOT/2+100)*cos(angle-cote*M_PI/2)+RAYON_ROBOT/2*cos(angle+M_PI),
                            (RAYON_ROBOT/2+100)*sin(angle-cote*M_PI/2)+RAYON_ROBOT/2*sin(angle+M_PI));
            VectDeux=VectUn+Position(3*RAYON_ROBOT/2*cos(angle),3*RAYON_ROBOT/2*sin(angle));
            VectTrois=Position(RAYON_ROBOT*cos(angle-cote*M_PI/2),RAYON_ROBOT*sin(angle-cote*M_PI/2));
            break;
    case 2:
            VectUn=Position((RAYON_ROBOT/2+100)*cos(angle+cote*M_PI/2)+RAYON_ROBOT/2*cos(angle+cote*M_PI),
                            (RAYON_ROBOT/2+100)*sin(angle+cote*M_PI/2)+RAYON_ROBOT/2*sin(angle+cote*M_PI));
            VectDeux=VectUn+Position(3*RAYON_ROBOT/2*cos(angle),3*RAYON_ROBOT/2*sin(angle));
            VectTrois=Position(RAYON_ROBOT*cos(angle+cote*M_PI/2),RAYON_ROBOT*sin(angle+cote*M_PI/2));
            break;
    case 10:
            VectUn=Position(RAYON_ROBOT*cos(angle)+RAYON_ROBOT/4*cos(angle-cote*M_PI/2),
                            RAYON_ROBOT*sin(angle)+RAYON_ROBOT/4*sin(angle-cote*M_PI/2));
            VectDeux=VectUn+Position(3*RAYON_ROBOT/2*cos(angle),3*RAYON_ROBOT/2*sin(angle));
            VectTrois=VectUn+Position(3*RAYON_ROBOT/2*cos(angle-cote*M_PI/2),3*RAYON_ROBOT/2*sin(angle-cote*M_PI/2));
            break;
    case 20:
            VectUn=Position(RAYON_ROBOT*cos(angle)-RAYON_ROBOT/4*cos(angle-cote*M_PI/2),
                            RAYON_ROBOT*sin(angle)-RAYON_ROBOT/4*sin(angle-cote*M_PI/2));
            VectDeux=VectUn+Position(3*RAYON_ROBOT/2*cos(angle),3*RAYON_ROBOT/2*sin(angle));
            VectTrois=VectUn-Position(3*RAYON_ROBOT/2*cos(angle-cote*M_PI/2),3*RAYON_ROBOT/2*sin(angle-cote*M_PI/2));
            break;
    case 50:
            VectUn=Position(RAYON_ROBOT*cos(angle)-RAYON_ROBOT/4*cos(angle-cote*M_PI/2),
                            RAYON_ROBOT*sin(angle)-RAYON_ROBOT/4*sin(angle-cote*M_PI/2));
            VectDeux=VectUn+Position(3*RAYON_ROBOT/2*cos(angle),3*RAYON_ROBOT/2*sin(angle));
            VectTrois=VectUn+Position(3*RAYON_ROBOT/2*cos(angle-cote*M_PI/2),3*RAYON_ROBOT/2*sin(angle-cote*M_PI/2));
            break;
    case 60:
            VectUn=Position(RAYON_ROBOT*cos(angle)+RAYON_ROBOT/4*cos(angle-cote*M_PI/2),
                            RAYON_ROBOT*sin(angle)+RAYON_ROBOT/4*sin(angle-cote*M_PI/2));
            VectDeux=VectUn+Position(3*RAYON_ROBOT/2*cos(angle),3*RAYON_ROBOT/2*sin(angle));
            VectTrois=VectUn-Position(3*RAYON_ROBOT/2*cos(angle-cote*M_PI/2),3*RAYON_ROBOT/2*sin(angle-cote*M_PI/2));
            break;
    case 30:
    case 70:
            VectUn=Position(RAYON_ROBOT*cos(angle)+3*RAYON_ROBOT/4*cos(angle-cote*M_PI/2),
                            RAYON_ROBOT*sin(angle)+3*RAYON_ROBOT/4*sin(angle-cote*M_PI/2));
            VectDeux=VectUn-Position(3*RAYON_ROBOT/2*cos(angle-cote*M_PI/2),3*RAYON_ROBOT/2*sin(angle-cote*M_PI/2));
            VectTrois=Position(3*RAYON_ROBOT/2*cos(angle),3*RAYON_ROBOT/2*sin(angle));
            break;
    case 100:
            VectUn=Position(RAYON_ROBOT/2*cos(angle-M_PI)+3*RAYON_ROBOT/4*cos(angle-cote*M_PI/2),
                            RAYON_ROBOT/2*sin(angle-M_PI)+3*RAYON_ROBOT/4*sin(angle-cote*M_PI/2));
            VectDeux=VectUn-Position(3*RAYON_ROBOT/2*cos(angle-cote*M_PI/2),3*RAYON_ROBOT/2*sin(angle-cote*M_PI/2));
            VectTrois=Position(3*RAYON_ROBOT/2*cos(angle-M_PI),3*RAYON_ROBOT/2*sin(angle-M_PI));
            break;
    default:
            VectUn=Position(0,0);
            VectDeux=Position(0,0);
            VectTrois=Position(0,0);
            break;
    }
    *positionRobotAdverseUn = VectUn + odometrie->getPos().getPosition();
    *positionRobotAdverseDeux= VectDeux + odometrie->getPos().getPosition();
    *positionRobotAdverseTrois= VectTrois + odometrie->getPos().getPosition();
}

bool ActionSuivreChemin::executer()
{
    strategieNormal=false;
    int cote=Strategie::getInstance()->getIsBlue() ? 1:-1;
    int timerCollision=0;
    Position positionActuelle = odometrie->getPos().getPosition();
    Angle angle = odometrie->getPos().getAngle();
//    bras = Bras::getBras();
    if (taille ==0)
        return true;

    Position trajet(chemin[pointSuivant].position-positionActuelle);

        nbCapteurs = intOfSensors();

        if(nbCapteurs>0)
        {
            affectePosRobotAdverse(nbCapteurs, cote);
            Position detectedPosition;
            switch(nbCapteurs)
            {
            case 10:
                    detectedPosition=positionActuelle+Position(330,120);
                    if((detectedPosition.x<droiteTotem) && (detectedPosition.x>gaucheTotem) && (detectedPosition.y<hautTotem) && (detectedPosition.y>basTotem))
                    {
                        strategieNormal=true;
                    }
                    else Command::freinageDUrgence(true);
            case 20:
                    detectedPosition=positionActuelle+Position(330,-120);
                    if((detectedPosition.x<droiteTotem) && (detectedPosition.x>gaucheTotem) && (detectedPosition.y<hautTotem) && (detectedPosition.y>basTotem))
                    {
                        strategieNormal=true;
                    }
                    else Command::freinageDUrgence(true);
            case 40:
                    detectedPosition=positionActuelle+Position(330,0);
                    if((detectedPosition.x<droiteTotem) && (detectedPosition.x>gaucheTotem) && (detectedPosition.y<hautTotem) && (detectedPosition.y>basTotem))
                    {
                        strategieNormal=true;
                    }
                    else Command::freinageDUrgence(true);
            default:
                    Command::freinageDUrgence(true);
                    break;
            }
        }

/*
            if(trajetPossible(chemin[pointSuivant].position,positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
            {
                strategieNormal=true;
            }
            else
            {
                strategieNormal=false;
                if(timerCollision<100)
                    {
                        timerCollision++;
                        Command::freinageDUrgence(true);
                    }
                else
                {
                    Command::freinageDUrgence(false);
                    Position objectif =chemin[pointSuivant].position;
                    float xv=objectif.x-positionActuelle.x;
                    float yv=objectif.y-positionActuelle.y;
                    Angle theta=2*atan(yv/(xv+sqrt(yv*yv + xv*xv)));
                    switch(nbCapteurs)
                    {
                    case 1:
                    case 2:
                            if(trajetPossible(positionActuelle+Position(3*RAYON_ROBOT/2*cos(angle),3*RAYON_ROBOT/2*sin(angle)),
                               positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                new CommandGoTo(positionActuelle+Position(3*RAYON_ROBOT/2*cos(angle),3*RAYON_ROBOT/2*sin(angle)));
                            }
                            else if (trajetPossible(positionActuelle-Position(3*RAYON_ROBOT/2*cos(angle),3*RAYON_ROBOT/2*sin(angle)),
                               positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                new CommandGoTo(positionActuelle-Position(3*RAYON_ROBOT/2*cos(angle),3*RAYON_ROBOT/2*sin(angle)),true);
                            }
                            else Command::freinageDUrgence(true);
                            break;
                    case 10:
                            if(trajetPossible(positionActuelle+Position(RAYON_ROBOT*cos(angle+cote*M_PI/4),RAYON_ROBOT*sin(angle+cote*M_PI/4)),
                               positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                new CommandGoTo(positionActuelle+Position(RAYON_ROBOT*cos(angle+cote*M_PI/4),RAYON_ROBOT*sin(angle+cote*M_PI/4)));
                            }
                            else if(trajetPossible(positionActuelle+Position(RAYON_ROBOT*cos(angle+cote*M_PI/2),RAYON_ROBOT*sin(angle+cote*M_PI/2)),
                                    positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                new CommandGoTo(positionActuelle+Position(RAYON_ROBOT*cos(angle+cote*M_PI/2),RAYON_ROBOT*sin(angle+cote*M_PI/2)));
                            }
                            else Command::freinageDUrgence(true);
                            break;
                    case 20:
                            if(trajetPossible(positionActuelle+Position(RAYON_ROBOT*cos(angle-cote*M_PI/4),RAYON_ROBOT*sin(angle-cote*M_PI/4)),
                               positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                new CommandGoTo(positionActuelle+Position(RAYON_ROBOT*cos(angle-cote*M_PI/4),RAYON_ROBOT*sin(angle-cote*M_PI/4)));
                            }
                            else if(trajetPossible(positionActuelle+Position(RAYON_ROBOT*cos(angle-cote*M_PI/2),RAYON_ROBOT*sin(angle-cote*M_PI/2)),
                                    positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                new CommandGoTo(positionActuelle+Position(RAYON_ROBOT*cos(angle-cote*M_PI/2),RAYON_ROBOT*sin(angle-cote*M_PI/2)));
                            }
                            else Command::freinageDUrgence(true);
                            break;
                    case 50:
                            if(theta<0 && trajetPossible(positionActuelle+Position(2*RAYON_ROBOT*cos(angle-cote*M_PI/2),2*RAYON_ROBOT*sin(angle-cote*M_PI/2)),
                                                         positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                CommandGoTo(positionActuelle+Position(2*RAYON_ROBOT*cos(angle-cote*M_PI/2),2*RAYON_ROBOT*sin(angle-cote*M_PI/2)));
                            }
                            else if(trajetPossible(positionActuelle+Position(3*RAYON_ROBOT/2*cos(angle+cote*M_PI/2),3*RAYON_ROBOT/2*sin(angle+cote*M_PI/2)),
                                                         positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                CommandGoTo(positionActuelle+Position(3*RAYON_ROBOT/2*cos(angle+cote*M_PI/2),3*RAYON_ROBOT/2*sin(angle+cote*M_PI/2)));
                            }
                            else Command::freinageDUrgence(true);
                            break;
                    case 60:
                            if(theta>0 && trajetPossible(positionActuelle+Position(2*RAYON_ROBOT*cos(angle+cote*M_PI/2),2*RAYON_ROBOT*sin(angle+cote*M_PI/2)),
                                                         positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                CommandGoTo(positionActuelle+Position(2*RAYON_ROBOT*cos(angle+cote*M_PI/2),2*RAYON_ROBOT*sin(angle+cote*M_PI/2)));
                            }
                            else if(trajetPossible(positionActuelle+Position(3*RAYON_ROBOT/2*cos(angle-cote*M_PI/2),3*RAYON_ROBOT/2*sin(angle-cote*M_PI/2)),
                                                         positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                CommandGoTo(positionActuelle+Position(3*RAYON_ROBOT/2*cos(angle-cote*M_PI/2),3*RAYON_ROBOT/2*sin(angle-cote*M_PI/2)));
                            }
                            else Command::freinageDUrgence(true);
                            break;
                    case 30:
                    case 70:
                            if(theta<0 && trajetPossible(positionActuelle+Position(RAYON_ROBOT*cos(angle-cote*M_PI/2),RAYON_ROBOT*sin(angle-cote*M_PI/2)),
                                                         positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                CommandGoTo(positionActuelle+Position(RAYON_ROBOT*cos(angle-cote*M_PI/2),RAYON_ROBOT*sin(angle-cote*M_PI/2)));
                            }
                            else if(theta>0 && trajetPossible(positionActuelle+Position(RAYON_ROBOT*cos(angle+cote*M_PI/2),RAYON_ROBOT*sin(angle+cote*M_PI/2)),
                                                         positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                            {
                                CommandGoTo(positionActuelle+Position(RAYON_ROBOT*cos(angle+cote*M_PI/2),RAYON_ROBOT*sin(angle+cote*M_PI/2)));
                            }
                            else Command::freinageDUrgence(true);
                            break;
                    case 100:
                            if(positionActuelle.x<500) Command::freinageDUrgence(true);
                            else
                            {
                                if(theta<0 && trajetPossible(positionActuelle+Position(RAYON_ROBOT*cos(angle-cote*M_PI/2),RAYON_ROBOT*sin(angle-cote*M_PI/2)),
                                                             positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                                {
                                    CommandGoTo(positionActuelle+Position(RAYON_ROBOT*cos(angle-cote*M_PI/2),RAYON_ROBOT*sin(angle-cote*M_PI/2)));
                                }
                                else if(theta>0 && trajetPossible(positionActuelle+Position(RAYON_ROBOT*cos(angle+cote*M_PI/2),RAYON_ROBOT*sin(angle+cote*M_PI/2)),
                                                                  positionRobotAdverseUn,positionRobotAdverseDeux,positionRobotAdverseTrois))
                                {
                                    CommandGoTo(positionActuelle+Position(RAYON_ROBOT*cos(angle+cote*M_PI/2),RAYON_ROBOT*sin(angle+cote*M_PI/2)));
                                }
                                else Command::freinageDUrgence(true);
                            }
                            break;
                    default:
                            Command::freinageDUrgence(true);
                            break;
                    }
                }
            }
        }
*/
       /* if(Sensors::getSensors()->detectedSharp(SharpSensor::FRONT_LEFT) || Sensors::getSensors()->detectedSharp(SharpSensor::FRONT_RIGTH) ||
           Sensors::getSensors()->detectedSharp(SharpSensor::BACK) || Sensors::getSensors()->detectedSharp(SharpSensor::RIGTH) ||
           Sensors::getSensors()->detectedSharp(SharpSensor::LEFT))
        {
            timerCollision=true;
            if(timerCollision<100)
            {
                timerCollision+=1;
                command::freinageDUrgence(true);
            }
            else new CommandGoTo(odometrie->getPos().getPosition()-Position(250,0));
        }*/

    if(nbCapteurs==0 /*|| strategieNormal*/)
    {
        Command::freinageDUrgence(false);
        timerCollision=0;
        if (!faitquelquechose)
        {
            faitquelquechose = true;
            new CommandGoTo(chemin[pointSuivant].position,chemin[pointSuivant].reculer);
        }

        if(trajet.x*trajet.x+trajet.y*trajet.y < DISTANCE_ARRET*DISTANCE_ARRET*1.3)
            {
                pointSuivant++;
                if(chemin[pointSuivant].balaiDroit)
                    Bras::getBras()->ouvrirBalaiDroit();
                else Bras::getBras()->fermerBalaiDroit();
                if(chemin[pointSuivant].balaiGauche)
                    Bras::getBras()->ouvrirBalaiGauche();
                else Bras::getBras()->fermerBalaiGauche();
                if(chemin[pointSuivant].rateau)
                    Bras::getBras()->monterRateau();
                else Bras::getBras()->descendreRateau();
                if(chemin[pointSuivant].desactiveCapteur)
                {
                    SharpSensor::estDesactive = true;
                }
                else
                {
                    SharpSensor::estDesactive = false;
                }
                if (pointSuivant < taille)
                    {
                        /*Sensors::getSensors()->activeAllSharp();
                        bool aFiniTourner = ((CommandGoTo*) Asservissement::asservissement->command)->getAFiniTourner();
                        if(aFiniTourner)
                        {
                            Sensors::getSensors()->desactiveSharp(SharpSensor::LEFT);
                            Sensors::getSensors()->desactiveSharp(SharpSensor::RIGTH);
                        }
                        else
                        {
                            Sensors::getSensors()->desactiveSharp(SharpSensor::FRONT);
                            Sensors::getSensors()->desactiveSharp(SharpSensor::FRONT_LEFT);
                            Sensors::getSensors()->desactiveSharp(SharpSensor::FRONT_RIGTH);
                        }*/
                if (chemin[pointSuivant].wait > 0)
                {
                    chemin[pointSuivant].wait--;
                    pointSuivant--;
                }
                else {
                        new CommandGoTo(chemin[pointSuivant].position,chemin[pointSuivant].reculer);
                }
                }

            }


        return (pointSuivant >= taille);
    }
    else
    {
        return false;
    }

}

