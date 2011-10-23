#include "Angle.h"

float wrapAngle(Angle angle)
{
    double tmp_val = fmod(angle, 2*M_PI);
    if(tmp_val<0) tmp_val += M_PI*2;
    return tmp_val <= M_PI ? tmp_val : tmp_val-2*M_PI;
}

bool angleEq(Angle a1, Angle a2)
{
    return (fabs(wrapAngle(a1 - a2))< 0.1);
}
