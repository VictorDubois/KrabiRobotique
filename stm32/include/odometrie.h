#ifndef ODOMETRIE_H_INCLUDED
#define ODOMETRIE_H_INCLUDED

#include "distance.h"
#include "PositionPlusAngle.h"

#ifndef ROBOTHW
class Odometrie
{
public:
	virtual PositionPlusAngle getPos()=0;
	virtual void setPos(PositionPlusAngle p)=0;
	virtual Angle getVitesseAngulaire()=0;
	virtual Distance getVitesseLineaire()=0;
	virtual void update() { };
};
#else

#include "quadrature_coder_handler.h"
class Odometrie
{
    public:
        Odometrie(/*PositionPlusAngle positionPlusAngleInitiale,*/ QuadratureCoderHandler* roueCodeuseGauche, QuadratureCoderHandler* roueCodeuseDroite);
        void update();

        QuadratureCoderHandler* roueCodeuseDroite;
        QuadratureCoderHandler* roueCodeuseGauche;

        PositionPlusAngle positionPlusAngle;

        Distance vitesseLineaire;
        Angle vitesseAngulaire;

        void setPos(PositionPlusAngle p)
        {
            positionPlusAngle = p;
        }

        PositionPlusAngle getPos()
        {
            return positionPlusAngle;
        }

        Angle getVitesseAngulaire()
        {
            return vitesseAngulaire;
        }

        Distance getVitesseLineaire()
        {
            return vitesseLineaire;
        }

    private:
        int32_t prevDeltaTicksRoueGauche;
        int32_t prevDeltaTicksRoueDroite;
        const double entraxe;
        const double rayonRoueCodeuse;
        const double nbTicksParTour;
        const double coeffDistance;
        const double coeffAngle;
};

#endif //ROBOTHW

#endif // ODOMETRIE_H_INCLUDED
