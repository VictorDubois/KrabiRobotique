#include "odometrie.h"

#include "stm32f10x_gpio.h"

Odometrie* Odometrie::odometrie = NULL;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Odometrie::Odometrie(QuadratureCoderHandler* roueCodeuseGauche, QuadratureCoderHandler* roueCodeuseDroite)
: rayonRoueCodeuse(RAYON_ROUE)
{

    vitesseLineaire =0;
    vitesseAngulaire=0;
    entraxe=TAILLE_ENTRAXE;
    rayonRoueCodeuse=RAYON_ROUE;
    nbTicksParTour=NBR_TICK_PAR_TOUR;

    coeffDistance=(M_PI*rayonRoueCodeuse)/nbTicksParTour;  //soit la distance parcouru par un demi tour de roue

    coeffAngle=-2*coeffDistance/entraxe; // soit l'angle = opposé sur hypothénus en faisant une approximation à l'ordre 1

    angle = 0;
    prevDeltaTicksRoueDroite = 0;
    prevDeltaTicksRoueGauche = 0;

    this->roueCodeuseGauche = roueCodeuseGauche;
    this->roueCodeuseDroite = roueCodeuseDroite;
    Odometrie::odometrie = this;

}

Odometrie::~Odometrie()
{
    delete roueCodeuseGauche;
    delete roueCodeuseDroite;
}

void Odometrie::update()
{

    // On a le moins pour prendre en compte que les deux roux codeuses sont montées dans des sens opposés car pas du même coté du robot
    int32_t deltaTicksRoueDroite = -roueCodeuseDroite->getTickValue();
    int32_t deltaTicksRoueGauche = roueCodeuseGauche->getTickValue();

    double filteredDeltaTicksRoueGauche = (deltaTicksRoueGauche+prevDeltaTicksRoueGauche)/2.0;

    double filteredDeltaTicksRoueDroite = (deltaTicksRoueDroite+prevDeltaTicksRoueDroite)/2.0;

    double tmpDeltaAngle = (filteredDeltaTicksRoueGauche-filteredDeltaTicksRoueDroite)*coeffAngle;  // cf coef angle

	double tmpDist = (filteredDeltaTicksRoueGauche+filteredDeltaTicksRoueDroite)*coeffDistance;     // soit le nombre moyen de tours de roue * le perimetre de la roue

    vitesseLineaire = Distance(tmpDist);
    vitesseAngulaire = Angle(tmpDeltaAngle);

	positionPlusAngle.setAngle(positionPlusAngle.getAngle()+vitesseAngulaire);
	positionPlusAngle.setPosition(positionPlusAngle.getPosition() + Position(tmpDist*cos(positionPlusAngle.getAngle()), tmpDist*sin(positionPlusAngle.getAngle())));    //mettre sinx si ça marche pas et non sin

	prevDeltaTicksRoueGauche = deltaTicksRoueGauche;    //Pour prendre la vitesse moyenne en utilisant le deplacement précédents.
	prevDeltaTicksRoueDroite = deltaTicksRoueDroite;    //idem pour l'angle

    angle = positionPlusAngle.getAngle()*180/M_PI; // Pour test
}

void Odometrie::setPos(const PositionPlusAngle& p)
{
    positionPlusAngle = p;
}

PositionPlusAngle Odometrie::getPos() const
{
    return positionPlusAngle;
}

Angle Odometrie::getVitesseAngulaire() const
{
    return vitesseAngulaire;
}

Distance Odometrie::getVitesseLineaire() const
{
    return vitesseLineaire;
}

void Odometrie::setX(Distance x)
{
    PositionPlusAngle posPA = Odometrie::odometrie->getPos();
    Position pos = posPA.getPosition();
    pos.setX(x);
    posPA.setPosition(pos);
    Odometrie::odometrie->setPos(posPA);
}

void Odometrie::setY(Distance y)
{
    PositionPlusAngle posPA = Odometrie::odometrie->getPos();
    Position pos = posPA.getPosition();
    pos.setY(y);
    posPA.setPosition(pos);
    Odometrie::odometrie->setPos(posPA);
}

void Odometrie::setAngle(Angle a)
{
    PositionPlusAngle posPA = Odometrie::odometrie->getPos();
    posPA.setAngle(a);
    Odometrie::odometrie->setPos(posPA);
}
