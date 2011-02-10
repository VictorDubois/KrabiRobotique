#include "Angle.h"
#include <math.h>

Angle::Angle()/* : angle(ang)*/
{
    angle = 0;
}

Angle::Angle(float ang)/* : angle(ang)*/
{
    angle = ang;
}

Angle::Angle(const Angle &original)/* : angle(original.angle)*/
{
    angle = original.angle;
}

bool Angle::presqueEgales(Angle &ang)
{
    //if((angle-ang.angle)*(angle-ang.angle)< 0.1)/* 0,1 = incertitude angulaire au carré que l'on tolère */
    if(fabs(angle-ang.angle)< 0.1)
        return true;
    return false;
}

Angle Angle::operator+(const Angle &ang)
{
      return Angle(angle + ang.angle);
}

Angle Angle::operator-(const Angle &ang)
{
      return Angle(angle - ang.angle);
}

Angle Angle::wrap()
{
    double tmp_val = fmod(angle, 2*M_PI);
    if(tmp_val<0) tmp_val += M_PI*2;
    return Angle(tmp_val <= M_PI ? tmp_val : tmp_val-2*M_PI);
}

Angle Angle::operator-() const
{
    return Angle(-angle);
}

Angle Angle::operator*(const double &scalaire){
    return Angle(angle * scalaire);
}

bool Angle::operator==(Angle &a)
{
    if ((angle==a.angle))
        return true;
    return false;
}

Angle Angle::operator=(const Angle &ang)
{
    angle=ang.angle;

    return *this;
}

Angle Angle::operator+=(const Angle &ang)
{
    angle+=ang.angle;

    return *this;
}

Angle Angle::operator-=(const Angle &ang)
{
    angle-=ang.angle;

    return *this;
}

float Angle::getValueInRadian(){
    return angle;
}
