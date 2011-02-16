#include "odometrie.h"
#include <stdint.h>
#include <math.h>

Odometrie::Odometrie(/*PositionPlusAngle positionPlusAngleInitiale,*/ QuadratureCoderHandler* roueCodeuseGauche, QuadratureCoderHandler* roueCodeuseDroite) :
    /*positionPlusAngle(positionPlusAngleInitiale),*/
    vitesseLineaire(0),
    vitesseAngulaire(0),
    entraxe(359*61.4/62.8),
    //entraxe(303),
    rayonRoueCodeuse(313/(2*M_PI) * 2210 / 2104),
    //rayonRoueCodeuse(50*2100/2039.77),
    //rayonRoueCodeuse(42),
    nbTicksParTour(2048*4),
    coeffDistance((M_PI*rayonRoueCodeuse)/nbTicksParTour),
    coeffAngle(2*coeffDistance/entraxe)
{
    prevDeltaTicksRoueDroite = 0;
    prevDeltaTicksRoueGauche = 0;
    this->roueCodeuseGauche = roueCodeuseGauche;
    this->roueCodeuseDroite = roueCodeuseDroite;
}

void Odometrie::update(){
    //float vitesseAngulaireRoueGauche = 100*roueCodeuseGauche->getTickValue()/(2048*4); //(en tours par secondes)
    //float vitesseAngulaireRoueDroite = 100*roueCodeuseDroite->getTickValue()/(2048*4);
    //roueCodeuseGauche->getTickValue();
    //roueCodeuseDroite->getTickValue();
    int32_t deltaTicksRoueGauche = -roueCodeuseGauche->getTickValue();
    int32_t deltaTicksRoueDroite = roueCodeuseDroite->getTickValue();

    int32_t filteredDeltaTicksRoueGauche = (deltaTicksRoueGauche+prevDeltaTicksRoueGauche)/2;
    int32_t filteredDeltaTicksRoueDroite = (deltaTicksRoueDroite+prevDeltaTicksRoueDroite)/2;

    double tmpDeltaAngle = (filteredDeltaTicksRoueDroite-filteredDeltaTicksRoueGauche)*coeffAngle;
	double tmpDist = (filteredDeltaTicksRoueGauche+filteredDeltaTicksRoueDroite)*coeffDistance;

    vitesseLineaire = Distance(tmpDist);
    vitesseAngulaire = Angle(tmpDeltaAngle);

    /*if(caca<100) coucou[caca] = vitesseAngulaire;
    caca++;*/

	positionPlusAngle.angle += vitesseAngulaire;
	positionPlusAngle.position += Position(tmpDist*cos(positionPlusAngle.angle), tmpDist*sin(positionPlusAngle.angle));
	//PositionPlusAngle didoudam = positionPlusAngle;
	//float didou = 3;
	prevDeltaTicksRoueGauche = deltaTicksRoueGauche;
	prevDeltaTicksRoueDroite = deltaTicksRoueDroite;
}
