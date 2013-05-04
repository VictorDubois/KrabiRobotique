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


#endif

