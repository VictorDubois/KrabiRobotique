#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include "variable.h"
#include "PositionPlusAngle.h"

#ifndef ROBOTHW
#include <iostream>
#endif

/**@brief Classe abstraite généralisant l'utilisation des commandes */
class Command
{
    public:
        /**@brief vitesse linéaire que l'on ne peut dépasser */
        static Vitesse vitesse_lineaire_max;
        /**@brief vitesse angulaire que l'on ne peut dépasser */
        static Vitesse vitesse_angulaire_max;
        /**@brief acceleration linéaire que l'on ne peut dépasser */
        static Acceleration acceleration_lineaire;
        /**@brief acceleration angulaire que l'on ne peut dépasser */
        static Acceleration acceleration_angulaire;
        /**@brief Constructeur par défaut. Il permet d'attribuer les commandes à l'asservissement qui fera en sorte que les commandes soient exécutées */
        Command();
        /**@brief Destructeur de la classe */
        ~Command();
        /**@brief Fonction appellée à chaque mise à jours ( 20ms) pour donner les différents vitesse à appliquer. Cette fonction est à déclarer dans les classes héritants de commande*/
        //virtual void update(PositionPlusAngle positionPlusAngleActuelle, Angle vitesse_angulaire_atteinte, float vitesse_lineaire_atteinte) = 0;
        virtual void update() = 0;
        /**@brief Retourne la vitesse linéaire que l'on veut atteindre. Cette fonction est à déclarer dans les classes héritants de commande*/
        virtual Vitesse getLinearSpeed() = 0;
        /**@brief Retourne la vitesse angulaire que l'on veut atteindre. Cette fonction est à déclarer dans les classes héritants de commande*/
        virtual Angle getAngularSpeed() = 0;
};

//On l'inclue à la fin du header parce que les déclarations n'en ont pas besoin mais les fonctions en on besoin.
//Si on l'inclue avant les déclaration, le header de asservissement a besoin de command mais celui ci n'est pas encore
//déclarer et il y a des soucie. Faites attentions aux inclusions cycliques, c'est fourbe
#include "asservissement.h"

#endif //COMMAND_H_INCLUDED

