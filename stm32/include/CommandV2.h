#ifndef COMMANDV2_H_INCLUDED
#define COMMANDV2_H_INCLUDED

#include "variable.h"
#include "command.h"
#include <math.h>
#include "strategie.h"
#include "Angle.h"
#include "odometrie.h"


/**@brief Cette classe permet de donner des ordres au robot et de les lui faire exécuter. C'est une V2 de la classe TrapezoidalCommand */
class CommandV2 : public Command
{
    public:
        /**@brief Constructeur par défault */
        CommandV2();
        /**@brief Déstructeur de la classe */
        ~CommandV2();
        /**@brief Retourne la vitesse lineaire à atteindre par le robot */
        float getLinearSpeed();
        /**@brief Retourne la vitesse angulaire à atteindre par le robot */
        Angle getAngularSpeed();
        /**@brief Indique si le robot a atteind sa destination ou non*/
        bool destinationAtteinte();
        /**@brief Pour donner l'ordre au robot d'aller à un endroit
        *@param Position position est la position que doit atteindre le robot. */
        void goTo(Position position);

    private:
        /**@brief C'est la vitesse linaire que l'on aimerai qu'il atteigne */
        float vitesse_lineaire_a_atteindre;
        /**@brief C'est la vitesse angulaire que l'on aimerai qu'il atteigne */
        float vitesse_angulaire_a_atteindre;
        /**@brief C'est la position que l'on aimerai qu'il atteigne */
        Position destination;
        /**@brief C'est l'angle que l'on aimerai qu'il atteigne */
        Angle destAngle;
        /**@brief Continet true si le robot a atteind sa destination ou non*/
        bool fini;
};


#endif
