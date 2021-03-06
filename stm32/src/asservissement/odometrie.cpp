#include "odometrie.h"

#ifdef ROBOTHW

#ifdef STM32F40_41xxx
    #include "stm32f4xx_gpio.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_gpio.h"
#endif

Odometrie* Odometrie::odometrie = NULL;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Odometrie::Odometrie(QuadratureCoderHandler* rcg, QuadratureCoderHandler* rcd)
: rayonRoueCodeuse(RAYON_ROUE), entraxe(TAILLE_ENTRAXE), nbTicksParTour(NBR_TICK_PAR_TOUR)
{
    vitesseLineaire =0;
    vitesseAngulaire=0;

    coeffDistance=(M_PI*rayonRoueCodeuse)/nbTicksParTour;  //soit la distance parcouru par un demi tour de roue

    coeffAngle=-2*coeffDistance/entraxe; // soit l'angle = opposé sur hypothénus en faisant une approximation à l'ordre 1

    for (int i = 0 ; i < tailleTabPrevTicks ; i++)
    {
        prevDeltaTicksRoueDroite[i] = 0;
        prevDeltaTicksRoueGauche[i] = 0;
    }

    this->roueCodeuseGauche = rcg;
    this->roueCodeuseDroite = rcd;

    if(odometrie == 0)
    {
        Odometrie::odometrie = this;
    }

    posX = 0.0;
    posY = 0.0;
    ang = 0.0;

    absAngle = 0.0;

}

Odometrie::~Odometrie()
{
    delete roueCodeuseGauche;
    delete roueCodeuseDroite;
}

//#include "remote.h"

void Odometrie::update()
{
    // pour filtrer les ticks
    for (int i = tailleTabPrevTicks-2 ; i >= 0; i--)
    {
        prevDeltaTicksRoueDroite[i+1] = prevDeltaTicksRoueDroite[i];
        prevDeltaTicksRoueGauche[i+1] = prevDeltaTicksRoueGauche[i];
    }

    // On a le moins pour prendre en compte que les deux roux codeuses sont montées dans des sens opposés car pas du même coté du robot
    prevDeltaTicksRoueDroite[0] = -roueCodeuseDroite->getTickValue();
    #if defined(STM32F40_41xxx) || defined(STM32F10X_MD)
        prevDeltaTicksRoueGauche[0] = -roueCodeuseGauche->getTickValue();
    #else
        prevDeltaTicksRoueGauche[0] = roueCodeuseGauche->getTickValue();
    #endif

    /*static int sum = 0;
    sum += prevDeltaTicksRoueGauche[0];

    static int test = 0;
    test++;
    if (test % 20 == 0)
        Remote::getSingleton()->log("Pika %d", sum);*/

    int32_t sommeGauche = 0;
    int32_t sommeDroite = 0;
    for (int i = 0 ; i < tailleTabPrevTicks ; i++)
    {
        sommeGauche += prevDeltaTicksRoueGauche[i];
        sommeDroite += prevDeltaTicksRoueDroite[i];
    }

    // double filteredDeltaTicksRoueGauche = (deltaTicksRoueGauche+prevDeltaTicksRoueGauche)/2.0;
    double filteredDeltaTicksRoueGauche = (double)sommeGauche/(double)tailleTabPrevTicks;

    // double filteredDeltaTicksRoueDroite = (deltaTicksRoueDroite+prevDeltaTicksRoueDroite)/2.0;
    double filteredDeltaTicksRoueDroite = (double)sommeDroite/(double)tailleTabPrevTicks;

    double tmpDeltaAngle = (filteredDeltaTicksRoueDroite-filteredDeltaTicksRoueGauche)*coeffAngle;  // cf coef angle

	double tmpDist = (filteredDeltaTicksRoueGauche+filteredDeltaTicksRoueDroite)*coeffDistance;     // soit le nombre moyen de tours de roue * le perimetre de la roue

    vitesseLineaire = Distance(tmpDist);

    vitesseAngulaire = Angle(tmpDeltaAngle);

	//positionPlusAngle.setAngle(positionPlusAngle.getAngle()+vitesseAngulaire);
	//positionPlusAngle.setPosition(positionPlusAngle.getPosition() + Position(tmpDist*cos(positionPlusAngle.getAngle()), tmpDist*sin(positionPlusAngle.getAngle())));    //mettre sinx si ça marche pas et non sin


    if (tmpDeltaAngle == 0.0)
    {
        posX += tmpDist*cos(ang);
        posY += tmpDist*sin(ang);
    }
    else
    {
        double rayonCourbure = tmpDist/tmpDeltaAngle;
        double distAvancee = rayonCourbure*sin(tmpDeltaAngle);
        double distTranslatee = rayonCourbure*(1.0-cos(tmpDeltaAngle));

        posX += distAvancee*cos(ang)-distTranslatee*sin(ang);
        posY += distAvancee*sin(ang)+distTranslatee*cos(ang);

        ang += vitesseAngulaire;
        absAngle += vitesseAngulaire;
        if (ang > M_PI)
            ang -= 2.0*M_PI;
        else if (ang < -M_PI)
            ang += 2.0*M_PI;
    }

    positionPlusAngle.setAngle(ang);
    positionPlusAngle.setX(posX);
    positionPlusAngle.setY(posY);
}

void Odometrie::setPos(const PositionPlusAngle& p)
{
    posX = p.getPosition().getX();
    posY = p.getPosition().getY();
    ang = p.getAngle();
    positionPlusAngle = p;
}

/*float Odometrie::getInterAxisDistance()
{
    return entraxe;
}

float Odometrie::getWheelSize()
{
    return rayonRoueCodeuse;
}*/

void Odometrie::setSettings(float interAxisDistance, float wheelSize)
{
    entraxe = interAxisDistance;
    rayonRoueCodeuse = wheelSize;

    coeffDistance=(M_PI*rayonRoueCodeuse)/nbTicksParTour;
    coeffAngle=-2*coeffDistance/entraxe;
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

Angle Odometrie::getAbsoluteAngle() const
{
    return absAngle;
}

void Odometrie::setX(Distance x)
{
    PositionPlusAngle posPA = getPos();
    Position pos = posPA.getPosition();
    pos.setX(x);
    posPA.setPosition(pos);
    setPos(posPA);
    odometrie->posX = x;
}

void Odometrie::setY(Distance y)
{
    PositionPlusAngle posPA = getPos();
    Position pos = posPA.getPosition();
    pos.setY(y);
    posPA.setPosition(pos);
    setPos(posPA);

    odometrie->posY = y;
}

void Odometrie::setAngle(Angle a)
{
    PositionPlusAngle posPA = getPos();
    posPA.setAngle(a);
    setPos(posPA);

    odometrie->ang = a;
}

float Odometrie::getInterAxisDistance()
{
    return entraxe;
}

float Odometrie::getWheelSize()
{
    return rayonRoueCodeuse;
}

#else

#include "robot.h"

/*** Simulateur ***/

Odometrie* Odometrie::odometrie = NULL;

//Odometrie class implementation for the simulation
//Yes, it's ugly ! it should not be in this file.
//But in a separate file
Odometrie::Odometrie(Robot* robot) : robot(robot)
{
    if (Odometrie::odometrie == 0)
        Odometrie::odometrie = this;
}

PositionPlusAngle Odometrie::getPos() const
{
    return robot->getPos();
}

float Odometrie::getInterAxisDistance()
{
    return TAILLE_ENTRAXE;
}

float Odometrie::getWheelSize()
{
    return RAYON_ROUE;
}

void Odometrie::setSettings(float interAxisDistance, float wheelSize)
{

}

Distance Odometrie::getVitesseLineaire() const
{
    return robot->getVitesseLineaire();
}

Angle Odometrie::getVitesseAngulaire() const
{
    return robot->getVitesseAngulaire();
}

void Odometrie::setPos(const PositionPlusAngle& p)
{
    robot->setPos(p);
}

#endif
