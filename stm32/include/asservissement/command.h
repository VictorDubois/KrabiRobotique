#ifndef COMMAND_H
#define COMMAND_H

#include "constantes.h"
#include "positionPlusAngle.h"

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
        virtual ~Command();

        /**@brief Fonction appellée à chaque mise à jours ( 20ms) pour donner les différents vitesse à appliquer. Cette fonction est à déclarer dans les classes héritants de commande*/
        //virtual void update(PositionPlusAngle positionPlusAngleActuelle, Angle vitesse_angulaire_atteinte, float vitesse_lineaire_atteinte) = 0;
        virtual void update() = 0;

        /**@brief Retourne la vitesse linéaire que l'on veut atteindre. Cette fonction est à déclarer dans les classes héritants de commande*/
        virtual Vitesse getLinearSpeed() = 0;

        /**@brief Retourne la vitesse angulaire que l'on veut atteindre. Cette fonction est à déclarer dans les classes héritants de commande*/
        virtual Angle getAngularSpeed() = 0;

        /** @brief Permet d'arrêter le robot imédiatement.
        *   @param doitFreiner Indique si on doit arrêter l'ordre imédiatement. */
        static void freinageDUrgence(bool doitFreiner);

        /** @brief Permet d'obtenir la valeur de stop et ainsi de s'avoir si on doit arrêter le robot ou pas.
        *   @return Retourne la valeur de stop */
        static bool getStop(void);

    private:

        /** @brief Indique si le robot doit s'arrêter imédiatement ou non. */
        static bool stop;
};

#endif //COMMAND_H

