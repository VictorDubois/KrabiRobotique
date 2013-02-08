#ifndef PION_H_INCLUDED
#define PION_H_INCLUDED

#include "Position.h"

#ifndef ROBOTHW
#include <QPainter>
#include "Box2D.h"
#endif

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

	Element(Position p, Type t)
	{
		this->p = p;
		this->type = t;
	}

	Element()
	{
	}

#ifndef ROBOTHW
	// /!\  Internal data for the simulation, don't use inside the Strategy class

	b2Body* body;

	Element(b2World & world, Position p, Type t);

	void paint(QPainter & pa);

	void updatePos();
#endif
};

#endif //PION_H_INCLUDED
