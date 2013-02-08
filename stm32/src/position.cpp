#include <math.h>

#include "position.h"


// Constructeur par défaut avec des coordonnées nulles.
Position::Position()
    : x(0), y(0)
{
}

Position::Position(Distance X, Distance Y)
    : x(X), y(Y)
{
}

Distance Position::getX() const
{
    return x;
}

Distance Position::getY() const
{
    return y;
}

void Position::setX(Distance X)
{
    x = X;
}

void Position::setY(Distance Y)
{
    y = Y;
}

Position Position::operator+(const Position &position) const
{
    Position resultat(x+position.x,y+position.y);
    return resultat;
}

Position Position::operator-(const Position &position) const
{
    Position resultat(x-position.x,y-position.y);
    return resultat;
}

void Position::operator=(Position position)
{

    x = position.x;
    y = position.y;

}

Position Position::operator+=(const Position &position)
{
    this->x+=position.x;
    this->y+=position.y;

    return *this;
}

Position Position::operator-=(const Position &position)
{
    this->x-=position.x;
    this->y-=position.y;

    return *this;
}

bool Position::presqueEgales(const Position &p) const
{
	return (distancePresqueEgales(x, p.x) && distancePresqueEgales(y,p.y));
}

bool Position::operator==(const Position &p) const
{
    return (x == p.x && y == p.y);
}

/*float sqrtx(float x)
{
    float r0 = 10.;
    float r1 = (r0+x/r0)/2.;
    while (fabs(r1-r0)>0.00001)
    {
        r0 = r1;
        r1 = (r0+x/r0)/2.;
    }
    return r1;
}*/

Distance Position::getNorme() const
{
    return Distance(sqrt(x*x+y*y));
}

/*Angle atanx(float x)
{
    float y = x*x;
    return x*(1-y*(0.3333333333+y*(0.2-y*0.142857143)));
}

Angle atan2x(float y,float x)
{
    Angle f = atanx (fabs(y/x));
    if (y>0)
    {
        return (x>0 ? f : (x=0 ? M_PI_2 : (M_PI-f) ));
    }
    else
    {
        return (x>0 ? -f : (x=0 ? -M_PI_2 : -(M_PI-f) ));
    }
}
*/
Angle Position::getAngle() const
{
	return atan2(y,x);
}
