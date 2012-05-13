#ifndef COMMANDRECULER_H
#define COMMANDRECULER_H

#include <command.h>
#include <Angle.h>

/** @brief Permet de reculer de manier fixe (créneau sans trapézoid) */
class CommandReculer : public Command
{
    public:
        /** @brief Default constructor */
        CommandReculer();
        /** @brief Default destructor */
        virtual ~CommandReculer();
        /** Met à jour l'ordre. vitesseLin = -VitesseLinMax/4; vitesseAng = 0; */
        void update();
    protected:
    private:
        Vitesse getLinearSpeed();
        /**@brief Retourne la vitesse angulaire que l'on veut atteindre. Cette fonction est à déclarer dans les classes héritants de commande*/
        Angle getAngularSpeed();
};

#endif // COMMANDRECULER_H
