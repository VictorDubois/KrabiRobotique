#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include <QPainter>
#include <QKeyEvent>
#include <boost/circular_buffer.hpp>
#include "PositionPlusAngle.h"

class Robot
{
private:
	bool manual;
public:

	PositionPlusAngle pos;
	PositionPlusAngle deriv;
	boost::circular_buffer<PositionPlusAngle> olds;
	class Asservissement* asservissement;
	class OdoRobot* odometrie;
	class Strategie* strategie;
	

	Robot();

	void paint(QPainter &p, int dt);
	void keyPressEvent(QKeyEvent* evt,bool press);
};

#endif //ROBOT_H_INCLUDED

