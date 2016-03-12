#include "simul/objet.h"
#include <QDebug>


Objet::Objet(b2World & world, Position p, Type type, Angle theta, QColor color) : p(p), type(type),  theta(theta), world(&world), p_color(color), radius(0.)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/100.,p.y/100.);
    bodyDef.angle = theta;

    body = world.CreateBody(&bodyDef);

    switch(type)
    {
    case SHELL:
    {
        b2CircleShape circle;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        circle.m_radius = 0.29f;
        circle.m_p.Set(0.,0.);
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.4f;
        fixtureDef.filter.maskBits = 0x3;
        fixtureDef.filter.categoryBits = 0x1;
        body->CreateFixture(&fixtureDef);

        radius = circle.m_radius;
        break;
    }

    case SANDCUBE:
    {
        b2Vec2 vertices[4];
        vertices[0].Set(0.0f, -0.58f);
        vertices[1].Set(0.0f, 0.0f);
        vertices[2].Set(-0.58f, 0.0f);
        vertices[3].Set(-0.58f, -0.58f);

        int32 count = 4;
        b2PolygonShape polygon;
        polygon.Set(vertices, count);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygon;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.4f;
        fixtureDef.filter.maskBits = 0x3;
        fixtureDef.filter.categoryBits = 0x1;
        body->CreateFixture(&fixtureDef);

        radius = 0.58f;
        break;
    }
    }
}

Objet::~Objet()
{
    world->DestroyBody(body);
}

void Objet::paint(QPainter &pa)
{
    switch (type)
    {
        case SHELL:
        {
            pa.setBrush(p_color);
            pa.setPen(p_color);

            pa.drawEllipse(QPoint(p.x,p.y),38,38);
            break;
        }
        case SANDCUBE:
        {
            p_color = QColor(232, 140, 0);
            pa.setBrush(p_color);
            pa.setPen(p_color);

            pa.drawRect(-29, -29, 58, 58);
            break;
        }
		default:
            break;
    }
    return;
}

void Objet::updatePos()
{
    p.x = 100*body->GetPosition().x;
    p.y = 100*body->GetPosition().y;

    theta = body->GetAngle()-3.14;

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

	float angularFriction = 0.5;
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

void Objet::moveOutOfField()
{
    body->SetTransform(b2Vec2(-1000., -1000.), body->GetAngle());
}

Position Objet::getPosition()
{
    return p;
}

Objet::Type Objet::getType()
{
    return type;
}

bool Objet::isNear(Position p, Distance radius)
{
    Vec2d delta = p - this->p;

    return (delta.getNorme() < radius + this->radius);
}
