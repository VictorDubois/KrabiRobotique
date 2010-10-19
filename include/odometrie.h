#ifndef ODOMETRIE_H_INCLUDED
#define ODOMETRIE_H_INCLUDED

#include "distance.h"
#include "PositionPlusAngle.h"

class Odometrie
{
public:
	virtual PositionPlusAngle getPos()=0;
	virtual void setPos(PositionPlusAngle p)=0;
	virtual Angle vitesseAngulaire()=0;
	virtual Distance vitesseLineaire()=0;
	virtual void update() { };
};


#ifdef ROBOTHW
#include "quadrature_coder_handler.h"
class OdometrieD : public Odometrie
{
    public:
        Odometrie(PositionPlusAngle positionPlusAngleInitiale, QuadratureCoderHandler* roueCodeuseGauche, QuadratureCoderHandler* roueCodeuseDroite);
        void update();

        QuadratureCoderHandler* roueCodeuseDroite;
        QuadratureCoderHandler* roueCodeuseGauche;

        PositionPlusAngle positionPlusAngle;

        Distance vitesseLineaire;
        Angle vitesseAngulaire;

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
