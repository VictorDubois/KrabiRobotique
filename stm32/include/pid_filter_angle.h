#ifndef PID_FILTER_ANGLE_H_INCLUDED
#define PID_FILTER_ANGLE_H_INCLUDED

#include "Angle.h"

class PIDFilterAngle{
    private:
    Angle sommeErreurs;
    Angle erreurPrecedente;
    static const float Kp, Ki, Kd;

    public:
    PIDFilterAngle();
    float getFilteredValue(Angle erreur);
};

#endif // PID_FILTER_ANGLE_H_INCLUDED
