#include "simul/element.h"

Element::Element(b2World & world, Position p, Type t)
{
	this->p = p;
	type = t;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x.getValueInMillimeters()/100., p.y.getValueInMillimeters()/100.);
	
	body = world.CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_p.Set(0.,0.);
	circle.m_radius = 1.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0; //0.3f;
	body->CreateFixture(&fixtureDef);
}

void Element::updatePos()
{
	p.x = 100.*body->GetPosition().x;
	p.y = 100.*body->GetPosition().y;
}
