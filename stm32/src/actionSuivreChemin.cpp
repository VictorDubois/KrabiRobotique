#include "actionSuivreChemin.h"
#include "sensors.h"

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
    if (taille ==0)
        return true;

    Position trajet(chemin[pointSuivant].position-odometrie->getPos().getPosition());

        if(chemin[pointSuivant].reculer)
        {
            if(getSensors()->detectedSharp(BACK))


        }
        else
        {
            if(getSensors()->detectedSharp(FRONT_LEFT) || getSensors()->detectedSharp(FRONT_RIGHT))


        }

    if (!faitquelquechose)
    {
        faitquelquechose = true;
        new CommandGoTo(chemin[pointSuivant].position);
    }

    if(trajet.x*trajet.x+trajet.y*trajet.y < 30.0f*30.0f)
    {
        pointSuivant++;
        if (pointSuivant < taille)
            new CommandGoTo(chemin[pointSuivant].position);

    }

    return (pointSuivant >= taille);

}

