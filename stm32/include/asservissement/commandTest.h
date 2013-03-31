#ifndef DEF_COMMANDTEST
#define DEF_COMMANDTEST

#include "command.h"

// commande de test pour que le robot avance à la vitesse maximale
class CommandTestAvancer : public Command
{
    public:

        CommandTestAvancer();
        virtual void update();

        // Avance à la vitesse maximale
        virtual Vitesse getLinearSpeed();

        // renvoit 0
        virtual Angle getAngularSpeed();
};

// commande de test pour que le robot tourne à la vitesse maximale (vers la gauche)
class CommandTestTournerGauche : public Command
{
    public:

        CommandTestTournerGauche();
        virtual void update();

        // renvoit 0
        virtual Vitesse getLinearSpeed();

        // tourne à la vitesse maximale (vers la gauche)
        virtual Angle getAngularSpeed();
};

#endif
