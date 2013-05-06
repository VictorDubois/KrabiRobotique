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

    bool m_fini;
    int cote;
    public:
        CommandAllerEnArcA(Position p, Position c, float v, bool reculer);

        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();

        // est ce que la commande a fini ?
        virtual bool fini() const;
};


class CommandAllerA : public Command
{
    Position but;
    float vFin;
    bool bonAngle;
    float linSpeed;
    float angSpeed;
    bool m_reculer;

    float derniereDistance;
    bool m_fini;
    public:
        CommandAllerA(Position p, bool reculer);

        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();

        // est ce que la commande a fini ?
        virtual bool fini() const;
};

class CommandTournerVers : public Command
{
    Position but;
    float linSpeed;
    float angSpeed;

    bool m_fini;
    int signeAngle;
    public:
        CommandTournerVers(Position p);

        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();

        // est ce que la commande a fini ?
        virtual bool fini() const;
};

class CommandAttendre : public Command
{
    int compte;
    public:
        CommandAttendre(int nbUpdates);

        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();

        // est ce que la commande a fini ?
        virtual bool fini() const;
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
