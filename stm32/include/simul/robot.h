#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include <QPainter>
#include <QKeyEvent>
#include <boost/circular_buffer.hpp>
#include "PositionPlusAngle.h"
#include <Box2D/Box2D.h>

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
	
	b2Body* body;

	Robot(b2World &world);

	void paint(QPainter &p, int dt);
	void keyPressEvent(QKeyEvent* evt,bool press);
	void updateForces(int dt);
};

#endif //ROBOT_H_INCLUDED

