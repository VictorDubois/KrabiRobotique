#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

#include "distance.h"
#include "Angle.h"

#ifndef ROBOTHW
#include <QPoint>
#endif

class Position{
public:
#ifndef ROBOTHW
	operator QPoint() { return QPoint(x,-y); }
#endif

    Distance x,y;
    Position() { x=0; y=0; }
    Position(Distance x, Distance y);
    Position operator+(const Position &position);
    Position operator-(const Position &position);
    Position operator=(const Position &position);
    Position operator+=(const Position &position);
    Position operator-=(const Position &position);
    bool operator==(const Position &p);
    bool presqueEgales(const Position &p);
    Distance getNorme(void);
    Angle getAngle(void);
};

#endif
