#include "command.h"

    ////////////////////////////////
    //      CommandAttendre       //
    ////////////////////////////////

class CommandAttendre : public Command
{
public:
    CommandAttendre(int nbUpdates);

    virtual void update();
    virtual Vitesse getLinearSpeed();
    virtual Angle getAngularSpeed();

    virtual bool fini() const;

private:
    int compte;
};

    ////////////////////////////////
    //    CommandTestAvancer      //
    ////////////////////////////////

class CommandTestAvancer : public Command
{
public:
    CommandTestAvancer();
    virtual void update();
    virtual Vitesse getLinearSpeed();
    virtual Angle getAngularSpeed();
};

    ////////////////////////////////
    //  CommandTestTournerGauche  //
    ////////////////////////////////

class CommandTestTournerGauche : public Command
{
public:
    CommandTestTournerGauche();
    virtual void update();
    virtual Vitesse getLinearSpeed();
    virtual Angle getAngularSpeed();
};
