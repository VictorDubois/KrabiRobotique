#include "actionSuivreChemin.h"
#include "Sensors.h"

ActionSuivreChemin::ActionSuivreChemin(ActionBase* tab, int n, Odometrie* odo)
:   chemin(NULL), taille(n), pointSuivant(0), odometrie(odo), faitquelquechose(false)
{
    if (n != 0)
        chemin = new ActionBase[n];

    for(int i = 0; i < n; i++)
        chemin[i] = tab[i];

}

ActionSuivreChemin::~ActionSuivreChemin()
{
    if (chemin != NULL)
        delete[] chemin;
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

bool toucherDeccordEtRobot(Position pos,Position* posRobotAdverse)
{
    bool toucher = false;
    toucher |= (pos.x<droiteTotem) && (pos.x>gaucheTotem) && (pos.y<hautTotem) && (pos.y>basTotem);
    toucher |= (pos.y<basTable) && (pos.y>hautTable) && (pos.x<gaucheTable) && (pos.x>droiteTable);
    toucher |= (pos.y>BasZoneCapitaine) && ((pos.x<zoneCapitaineRouge) || (pos.x>zoneCapitaineBleu));
    toucher |= (pos.y<hautZoneDeDepart) && ((pos.x<zoneDeDepartRouge) || (pos.x>zoneDeDepartBleu));

}

bool ActionSuivreChemin::executer()
{
    int timerCollision=0;
    if (taille ==0)
        return true;

    Position trajet(chemin[pointSuivant].position-odometrie->getPos().getPosition());

       /* if(chemin[pointSuivant].reculer)
        {
            if(getSensors()->detectedSharp(BACK))
            {
                if(timerCollision<100)
                {
                    timerCollision+=1;
                }
                else new CommandGoTo(odometrie->getPos().getPosition()-Position(250,0));
            }
        }
        else
        {
            if(getSensors()->detectedSharp(FRONT_LEFT) || getSensors()->detectedSharp(FRONT_RIGHT))
            {
                if(timerCollision<100)
                {
                    timerCollision+=1;
                }
                else if(!getSensors()->detectedSharp(FRONT_LEFT))
                {
                    if(getSensors()->getValueUltrasound(Front)<100)
                    {
                        PositionPlusAngle** CheminTheorique = CommandGoTo::path(position(123,456));
                        bool toucher = false;
                        for(int i,i<,i+=5)
                        {
                            toucher |= eviterDeccordEtRobot;
                        }
                    }
                }
            }
        }*/

       /* if(Sensors::getSensors()->detectedSharp(SharpSensor::FRONT_LEFT) || Sensors::getSensors()->detectedSharp(SharpSensor::FRONT_RIGTH) ||
           Sensors::getSensors()->detectedSharp(SharpSensor::BACK) || Sensors::getSensors()->detectedSharp(SharpSensor::RIGTH) ||
           Sensors::getSensors()->detectedSharp(SharpSensor::LEFT))
        {
            timerCollision=true;
            if(timerCollision<100)
            {
                timerCollision+=1;
            }
            else new CommandGoTo(odometrie->getPos().getPosition()-Position(250,0));
        }*/

    if(Sensors::getSensors()->detectedSharp().getSize()==0)
    {
        if (!faitquelquechose)
        {
            faitquelquechose = true;
            new CommandGoTo(chemin[pointSuivant].position);
        }

        if(trajet.x*trajet.x+trajet.y*trajet.y < 60.0f*60.0f)
        {
            pointSuivant++;
            if (pointSuivant < taille)
                new CommandGoTo(chemin[pointSuivant].position,chemin[pointSuivant].reculer);

        }


        return (pointSuivant >= taille);
    }

}

