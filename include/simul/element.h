#ifndef PION_H_INCLUDED
#define PION_H_INCLUDED

#include "Position.h"
#include <QPainter>
#include "Box2D/Box2D.h"

class Element
{
public:
	Position p;
	enum Type
	{
		Pion = 0,
		Dame = 1,
		Roi = 2
	};

	Type type;

	b2Body* body;

	Element(b2World & world, Position p, Type t);

	void paint(QPainter & pa)
	{

		pa.setBrush(QBrush(QColor("yellow")));
		pa.setPen(QBrush(QColor("yellow")));

		pa.drawEllipse(QPoint(p.x,p.y),100,100);
	}

	void updatePos();
};

#endif //PION_H_INCLUDED
