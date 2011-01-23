#ifndef PION_H_INCLUDED
#define PION_H_INCLUDED

#include "Position.h"
#include <QPainter>
#include "Box2D.h"

class Element
{
public:
	Position p;
	enum Type
	{
		Pawn = 0,
		Queen = 1,
		King = 2
	};

	Type type;
	unsigned int multiplier;

	b2Body* body;

	Element(b2World & world, Position p, Type t);

	void paint(QPainter & pa);

	void updatePos();
};

#endif //PION_H_INCLUDED
