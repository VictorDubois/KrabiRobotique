#include "odometrie.h"


Odometrie::Odometrie(QuadratureCoderHandler* roueCodeuseGauche, QuadratureCoderHandler* roueCodeuseDroite) :
    vitesseLineaire(0),
    vitesseAngulaire(0),
    entraxe(TAILLE_ENTRAXE),
    rayonRoueCodeuse(RAYON_ROUE),
    nbTicksParTour(NBR_TICK_PAR_TOUR),
    coeffDistance((M_PI*rayonRoueCodeuse)/nbTicksParTour),  //soit la distance parcouru par un demi tour de roue
    coeffAngle(2*coeffDistance/entraxe) // soit l'angle = opposé sur hypothénus en faisant une approximation à l'ordre 1
{
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

/* Je ne vois pas l'utilité mais à remettre si ça bug
float sinx(float x)
{
    static const float a[] = {-.1666666664,.0083333315,-.0001984090,.0000027526,-.0000000239};
    float xsq = x*x;
    float temp = x*(1 + a[0]*xsq + a[1]*xsq*xsq + a[2]* xsq*xsq*xsq+a[3]*xsq*xsq*xsq*xsq+ a[4]*xsq*xsq*xsq*xsq*xsq);
    return temp;
}*/

void Odometrie::update(){
    int32_t deltaTicksRoueGauche = -roueCodeuseGauche->getTickValue(); //On a le moins pour prendre en compte que les deux roux codeuses sont monté dans des sens opposées car pas du même coté du robot
    int32_t deltaTicksRoueDroite = roueCodeuseDroite->getTickValue();
    /*Remettre ce coefficient si ça bug mais juste en lisant le code j'en vois pas l'utilité
    if (deltaTicksRoueDroite > 0)
        deltaTicksRoueDroite*=1.25;*/

    int32_t filteredDeltaTicksRoueGauche = (deltaTicksRoueGauche+prevDeltaTicksRoueGauche)/2;
    int32_t filteredDeltaTicksRoueDroite = (deltaTicksRoueDroite+prevDeltaTicksRoueDroite)/2;

    double tmpDeltaAngle = (filteredDeltaTicksRoueDroite-filteredDeltaTicksRoueGauche)*coeffAngle;  //cf coef angle
	double tmpDist = (filteredDeltaTicksRoueGauche+filteredDeltaTicksRoueDroite)*coeffDistance;     // soit le nomre moyen de tours de roue * le perimetre de la roue

    vitesseLineaire = Distance(tmpDist);
    vitesseAngulaire = Angle(tmpDeltaAngle);

	positionPlusAngle.setAngle(positionPlusAngle.getAngle()+vitesseAngulaire);
	positionPlusAngle.setPosition(positionPlusAngle.getPosition()+ Position(tmpDist*cos(positionPlusAngle.getAngle()), tmpDist*sin(positionPlusAngle.getAngle())));    //mettre sinx si ça marche pas et non sin

	prevDeltaTicksRoueGauche = deltaTicksRoueGauche;    //Pour prendre la vitesse moyenne en utilisant le deplacement précédents.
	prevDeltaTicksRoueDroite = deltaTicksRoueDroite;    //idem pour l'angle
}

void Odometrie::setPos(PositionPlusAngle p)
{
    positionPlusAngle = p;
}

PositionPlusAngle Odometrie::getPos()
{
    return positionPlusAngle;
}

Angle Odometrie::getVitesseAngulaire()
{
    return vitesseAngulaire;
}

Distance Odometrie::getVitesseLineaire()
{
    return vitesseLineaire;
}
