#include "command.h"

class CommandAllerEnArcA : public Command
{
    Position but;
    float vMax;
    bool bonAngle;
    float linSpeed;
    float angSpeed;
    bool m_reculer;
    Position centre;
    public:
        CommandAllerEnArcA(Position p, Position c, float v, bool reculer);

        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();
};


class CommandAllerA : public Command
{
    Position but;
    float vFin;
    bool bonAngle;
    float linSpeed;
    float angSpeed;
    bool m_reculer;
    public:
        CommandAllerA(Position p, bool reculer);

        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();
};

class CommandTournerVers : public Command
{
    Position but;
    float linSpeed;
    float angSpeed;
    public:
        CommandTournerVers(Position p);

        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();
};

class CommandTestAvancer : public Command
{
    public:

        CommandTestAvancer();
        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();
};

class CommandTestTournerGauche : public Command
{
    public:

        CommandTestTournerGauche();
        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();
};
