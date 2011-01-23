#ifndef PID_FILTER_DISTANCE_H_INCLUDED
#define PID_FILTER_DISTANCE_H_INCLUDED

#include "distance.h"

class PIDFilterDistance{
    private:
    Distance sommeErreurs;
    Distance erreurPrecedente;
    static const float Kp, Ki, Kd;

    public:
    PIDFilterDistance();
    float getFilteredValue(Distance erreur);
};

#endif // PID_FILTER_DISTANCE_H_INCLUDED
