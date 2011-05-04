#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include <QPainter>
#include <QKeyEvent>
#include <boost/circular_buffer.hpp>
#include "PositionPlusAngle.h"
#include <Box2D.h>

class Robot
{
private:
	bool manual;
	b2World &world;
public:

	PositionPlusAngle pos;
	PositionPlusAngle deriv;
	boost::circular_buffer<PositionPlusAngle> olds;
	class Asservissement* asservissement;
	class Odometrie* odometrie;
	class Strategie* strategie;
	class Pince * pince;
	
	b2Body* body;
	b2Joint* joint;
	class Element* elem;
	unsigned int level;

	Robot(b2World &world);

	void paint(QPainter &p, int dt);
	void keyPressEvent(QKeyEvent* evt,bool press);
	void updateForces(int dt);
	void interact(std::vector<class Element*> &elements);
	void makeJoint();
	void setLevel();
};

#endif //ROBOT_H_INCLUDED

