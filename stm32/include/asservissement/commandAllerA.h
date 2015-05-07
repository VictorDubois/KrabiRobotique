#include "command.h"

class CommandAllerA : public Command
{
public:
    CommandAllerA(Position p, bool reculer, float vitesseLineaireMax = VITESSE_LINEAIRE_MAX, float vitesseFin = 0.0f, float precisionAngle = -1.);

    virtual void update();
    //virtual void limitSpeed();

    void smoothMovement(Position nextGoal, float smoothFactor);

private:
    Position but, nextGoal;

    bool bonAngle, m_reculer, requireSmoothMovement, angleSmoothEnd;
    float vitesseLinMax, lastDistance, precisionAngle, smoothFactor, vFin2;// vitesse finale * vitesse finale
};
