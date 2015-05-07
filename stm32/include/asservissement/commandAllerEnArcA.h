#include "command.h"

class CommandAllerEnArcA : public Command
{

public:
    CommandAllerEnArcA(Position p, Position c, float v, bool reculer);

    virtual void update();

private:
    Position but, centre;

    float vMax;
    bool bonAngle, m_reculer;
    int cote;
};
