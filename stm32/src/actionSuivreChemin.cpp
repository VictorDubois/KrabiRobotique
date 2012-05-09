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
                else new CommandGoTo(odometrie->getPos().getPosition()-Position(250,0));
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

