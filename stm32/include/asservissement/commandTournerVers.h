#include "command.h"

class CommandTournerVers : public Command
{
public:
    CommandTournerVers(Position p, float maxSpeed = VITESSE_ANGULAIRE_MAX);
    CommandTournerVers(Angle a, float maxSpeed = VITESSE_ANGULAIRE_MAX);

    virtual void update();
    virtual Vitesse getLinearSpeed();

private:
    Position but;

    float butAngle, maxAngSpeed;

    bool useAngle;
    int signeAngle;
};
