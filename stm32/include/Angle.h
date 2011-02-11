#ifndef ANGLE_H_INCLUDED
#define ANGLE_H_INCLUDED

#include <math.h>

typedef double Angle;

inline float wrapAngle(float angle)
{
    double tmp_val = fmod(angle, 2*M_PI);
    if(tmp_val<0) tmp_val += M_PI*2;
    return tmp_val <= M_PI ? tmp_val : tmp_val-2*M_PI;
}

inline bool angleEq(Angle a1, Angle a2)
{
    //if((angle-ang.angle)*(angle-ang.angle)< 0.1)/* 0,1 = incertitude angulaire au carré que l'on tolère */
    if(fabs(wrapAngle(a1 - a2))< 0.1)
        return true;
    return false;
}

#if 0
class Angle
{
    private:
    float angle;

    public:
    Angle();
    Angle(float angle);
    Angle operator+(const Angle &angle);
    Angle operator-(const Angle &angle);
    Angle operator-() const;
    Angle operator=(const Angle &angle);
    Angle operator+=(const Angle &angle);
    Angle operator-=(const Angle &angle);
    Angle operator*(const double &scalaire);
    bool operator==(Angle &a);
    bool presqueEgales(Angle &ang);
    Angle(const Angle &original);
    float getValueInRadian();
    Angle wrap();
};
#endif

#endif // ANGLE_H_INCLUDED

