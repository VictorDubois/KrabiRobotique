#ifndef PION_H_INCLUDED
#define PION_H_INCLUDED

#include "Position.h"
#include <QPainter>

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

	Element(Position p, Type t)
	{
		this->p = p;
		type = t;
	}

	void paint(QPainter & pa)
	{

		pa.setBrush(QBrush(QColor("yellow")));
		pa.setPen(QBrush(QColor("yellow")));

		pa.drawEllipse(QPoint(p.x.getValueInMillimeters(),p.x.getValueInMillimeters()),150,150);
	}
};

#endif //PION_H_INCLUDED
