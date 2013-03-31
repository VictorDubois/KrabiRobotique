#ifndef DEF_COMMANDLOOKAT
#define DEF_COMMANDLOOKAT

#include "command.h"
#include "position.h"

// le robot tourne sur place vers la position indiquée
class CommandLookAt : public Command
{
    // point visé
    Position but;

    // vitesse angulaire
    float angSpeed;

    public:

        // le robot se tourne vers le point donné
        CommandLookAt(Position objectif);

        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();
};

// le robot se tourne vers la position et y avance (ou recule) en ligne droite
class CommandAllerA : public Command
{
    // point visé
    Position but;

    // le robot peut il avancer ?
    bool bonAngle;

    // vitesse angulaire
    float angSpeed;

    // vitesse linéaire
    float linSpeed;

    // le robot doit il reculer ?
    bool m_reculer;

    public:

        // le robot se tourne vers le point donné et y avance
        CommandAllerA(Position objectif, bool reculer = false);

        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();
};

#endif

