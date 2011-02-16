#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include "Angle.h"
#include "PositionPlusAngle.h"

class Command
{
public: 
        static float vitesse_lineaire_max;
        static float vitesse_angulaire_max;
        static float acceleration_lineaire;
        static float acceleration_angulaire;


	Command();
	~Command();
	virtual void update(PositionPlusAngle positionPlusAngleActuelle, Angle vitesse_angulaire_atteinte, float vitesse_lineaire_atteinte) = 0;

	virtual float getLinearSpeed() = 0;
	virtual Angle getAngularSpeed() = 0;
};

class TrapezoidalCommand : public Command
{
private:
        float vitesse_lineaire_a_atteindre;
        float vitesse_angulaire_a_atteindre;
        Position destination;
        Angle destAngle;
        bool en_mouvement;
        bool direction;
        bool stop;
public:
	TrapezoidalCommand();
	~TrapezoidalCommand();
	void update(PositionPlusAngle positionPlusAngleActuelle, Angle vitesse_angulaire_atteinte, float vitesse_lineaire_atteinte);

        void goTo(Position position, bool stop=true);
        void goToDirection(Angle angle);
        void recule(Distance distance);
        void tourne(Angle angle);
        Distance getVitesseLineaireAfterTrapeziumFilter(Distance vitesse_lineaire_atteinte, Distance distance_restante, Angle angle_restant);
        Angle getVitesseAngulaireAfterTrapeziumFilter(Angle vitesse_angulaire_atteinte, Angle angle_restant);

	float getLinearSpeed()
	{
		return vitesse_lineaire_a_atteindre;
	}

	Angle getAngularSpeed()
	{
		return vitesse_angulaire_a_atteindre;
	}

};

#endif //COMMAND_H_INCLUDED

