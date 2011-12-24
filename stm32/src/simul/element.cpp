#include "element.h"

 Element::Element(b2World & world, Position p, Type t)
{
	this->p = p;
	type = t;
	multiplier = 1;

	b2BodyDef bodyDef;
#ifndef BOX2D_2_0_1
	bodyDef.type = b2_dynamicBody;
#endif
	bodyDef.position.Set(p.x/100., p.y/100.);
	
	body = world.CreateBody(&bodyDef);

#ifdef BOX2D_2_0_1
	b2CircleDef circle;
	b2CircleDef &fixtureDef = circle;
	circle.radius = 1.0f;
	circle.localPosition.Set(0.,0.);
#define CreateFixture CreateShape
#else
	b2CircleShape circle;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	circle.m_radius = 1.0f;
	circle.m_p.Set(0.,0.);
#endif

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.4f;

	//Categorie :
	//1 - normal
	//2 - Dame or Roi
	//4 - Objet élevé
	fixtureDef.filter.maskBits = 0x3;
	fixtureDef.filter.categoryBits = 0x1;
	if(type != Pawn)
	{
		fixtureDef.filter.categoryBits = 0x2;
		fixtureDef.filter.maskBits |= 0x4;
	}
	body->CreateFixture(&fixtureDef);
#ifdef BOX2D_2_0_1
	body->SetMassFromShapes();
#endif
}

void Element::updatePos()
{
	p.x = 100.*body->GetPosition().x;
	p.y = 100.*body->GetPosition().y;

	float friction = 0.5;
	b2Vec2 velocity = body->GetLinearVelocity();
	float32 speed = velocity.Length();
	
	if(speed > FLT_EPSILON)
	{
		float32 newSpeed = speed - friction;
		if(newSpeed < 0)
			newSpeed = 0;
		velocity *= newSpeed/speed;
		body->SetLinearVelocity(velocity);
	}

	float angularFriction = 0.1;
	float angular = body->GetAngularVelocity();
	if(angular > 0)
	{
		angular -= angularFriction;
		if(angular < 0)
			angular = 0;
	}
	else
	{
		angular += angularFriction;
		if(angular > 0)
			angular = 0;
	}
	body->SetAngularVelocity(angular);
}

void Element::paint(QPainter & pa)
{

	pa.setBrush(QBrush(QColor("yellow")));
	pa.setPen(QBrush(QColor("yellow")));

	pa.drawEllipse(QPoint(p.x,-p.y),100,-100);

	pa.setBrush(QBrush(QColor("black")));
	pa.setPen(QBrush(QColor("black")));
	QFont font;
	font.setPointSize(30);
	pa.setFont(font);

	QString text;
	if(type == Pawn)
	{
		if(multiplier > 1)
			text = QString::number(multiplier);
	}
	else
	{
		if(type == Queen)
			text = "Q";
		else
			text = "K";
		if(multiplier > 1)
			text += QString::fromStdWString(L"×") + QString::number(multiplier);
	}

	pa.drawText(p.x-80, -p.y+80, 160, -160, Qt::AlignCenter, text);
}
