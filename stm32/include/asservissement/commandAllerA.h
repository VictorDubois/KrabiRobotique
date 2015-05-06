#include "command.h"

    ////////////////////////////////
    //    CommandAllerEnArcA      //
    ////////////////////////////////

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

    ////////////////////////////////
    //       CommandAllerA        //
    ////////////////////////////////

class CommandAllerA : public Command
{
public:
    CommandAllerA(Position p, bool reculer, float vitesseLineaireMax = VITESSE_LINEAIRE_MAX, float vitesseFin = 0.0f, float precisionAngle = -1.);

    virtual void update();
    virtual Vitesse getLinearSpeed();
    virtual Angle getAngularSpeed();
    virtual void resetSpeeds();
    //virtual void limitSpeed();

    void smoothMovement(Position nextGoal, float smoothFactor);

    // est ce que la commande a fini ?
    virtual bool fini() const;

private:
    Position but, nextGoal;
    bool bonAngle, m_reculer, m_fini, requireSmoothMovement;
    float vitesseLinMax, linSpeed, angSpeed, lastDistance, precisionAngle, smoothFactor, vFin2;// vitesse finale * vitesse finale
};

    ////////////////////////////////
    //    CommandTournerVers      //
    ////////////////////////////////

class CommandTournerVers : public Command
{
    Position but;
    float angSpeed, butAngle;

    bool m_fini, useAngle;
    int signeAngle;
    public:
        CommandTournerVers(Position p, float maxSpeed = VITESSE_ANGULAIRE_MAX);
        CommandTournerVers(Angle a, float maxSpeed = VITESSE_ANGULAIRE_MAX);

        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();

        // est ce que la commande a fini ?
        virtual bool fini() const;

private:
        float maxAngSpeed;
};


    ////////////////////////////////
    //       CommandVirage        //
    ////////////////////////////////

// fait un virage d'un certain angle à la vitesse max suivant un certain rayon de courbure
// arrive avec un certaine vitesse de fin
// marche que vers l'avant
class CommandVirage : public Command
{
    float rayonCourbure;
    float linSpeed;
    float angSpeed;
    float angleVise;

    float vitesseLinMax;
    float vFin2; // vitesse finale * vitesse finale
    bool m_fini;

    public:
        // rayon > 0
        // angle > 0 : vers la gauche, angle < 0 : vers la droite
        CommandVirage(float rayon, float angle, float vitesseLineaireMax = VITESSE_LINEAIRE_MAX, float vitesseFin = 0.0f);

        virtual void update();
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();

        // est ce que la commande a fini ?
        virtual bool fini() const;
};

    ////////////////////////////////
    //      CommandAttendre       //
    ////////////////////////////////

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
