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
	fixtureDef.friction = 0.4f;
	body->CreateFixture(&fixtureDef);
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
