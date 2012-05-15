#include "Angle.h"

float wrapAngle(Angle angle)
{
   /* double tmp_val = fmod(angle, 2*M_PI);
    if(tmp_val<0) tmp_val += M_PI*2;
    return tmp_val <= M_PI ? tmp_val : tmp_val-2*M_PI;
    */
    float a = angle;
    float M_2PI = 2*M_PI;
    if (angle > 0)
    {
        while (a > M_PI)
        {
            a -= M_2PI;
        }
    }
    else
    {
        while (a<-M_PI)
        {
            a += M_2PI;
        }
    }
    return a;
    /*
    if (angle >= 0)
    {
        return (fmod(angle+M_PI,2*M_PI)-M_PI);
    }
    else
    {
        return (fmod(angle-M_PI,2*M_PI)+M_PI);
    }*/
}

bool angleEq(Angle a1, Angle a2)
{
    return (fabs(wrapAngle(a1 - a2))< 0.1);
}

/*float sinx(float x)
{
    static const float a[] = {-.1666666664,.0083333315,-.0001984090,.0000027526,-.0000000239};
    float xsq = x*x;
    float temp = x*(1 + xsq*(a[0] + xsq*(a[1] + xsq*(a[2]+ xsq*(a[3]+ xsq*a[4])))));
    return temp;
}

float cosx(float x)
{
    return sinx(M_PI/2+x);
}
*/
