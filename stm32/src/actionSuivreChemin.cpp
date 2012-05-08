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
    bool timerCollision=false;
    if (taille ==0)
        return true;

    Position trajet(chemin[pointSuivant].position-odometrie->getPos().getPosition());

       /* if(chemin[pointSuivant].reculer)
        {
            if(getSensors()->detectedSharp(BACK))


        }
        else
        {
            if(getSensors()->detectedSharp(FRONT_LEFT) || getSensors()->detectedSharp(FRONT_RIGHT))


        }*/

     /*   if(Sensors::getSensors()->detectedSharp(SharpSensor::FRONT_LEFT) || Sensors::getSensors()->detectedSharp(SharpSensor::FRONT_RIGTH) ||
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

    if(trajet.x*trajet.x+trajet.y*trajet.y < 50.0f*50.0f)
    {
        pointSuivant++;
        if (pointSuivant < taille)
            new CommandGoTo(chemin[pointSuivant].position);

    }


    return (pointSuivant >= taille);

}

