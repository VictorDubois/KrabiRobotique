#include "Angle.h"
#include "PositionPlusAngle.h"

class Command
{
private:
        float vitesse_lineaire_a_atteindre;
        Angle vitesse_angulaire_a_atteindre;
        float vitesse_lineaire_max;
        Angle vitesse_angulaire_max;
        float acceleration_lineaire;
        Angle acceleration_angulaire;

        Position destination;
        Angle destAngle;
        bool en_mouvement;
        bool direction;
        bool stop;
public:
	Command();
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

