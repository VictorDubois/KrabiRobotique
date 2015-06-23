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
    case GLASS:
    {
        b2CircleShape circle;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
		circle.m_radius = 0.4f;
        circle.m_p.Set(0.,0.);
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.4f;
        fixtureDef.filter.maskBits = 0x3;
        fixtureDef.filter.categoryBits = 0x1;
        body->CreateFixture(&fixtureDef);

        radius = circle.m_radius;
        break;
    }

    case GIFT:
    {
        b2Vec2 vertices[4];
		vertices[0].Set(0.0f, -0.28f);
        vertices[1].Set(0.0f, 0.0f);
        vertices[2].Set(-1.5f, 0.0f);
		vertices[3].Set(-1.5f, -0.28f);

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

        radius = 1.5f;
        break;
    }

    case FIREUP:
    {
        b2Vec2 vertices[4];
        vertices[0].Set(0.0f, -0.3f);
        vertices[1].Set(0.0f, 0.0f);
        vertices[2].Set(-1.4f, 0.0f);
        vertices[3].Set(-1.4f, -0.3f);

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

        radius = 1.4f;
        break;
    }

    case TORCH:
    {
        b2CircleShape circle;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        circle.m_radius = 0.8f;
        circle.m_p.Set(0.,0.);
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.4f;
        fixtureDef.filter.maskBits = 0x3;
        fixtureDef.filter.categoryBits = 0x1;
        body->CreateFixture(&fixtureDef);

        radius = circle.m_radius;
        break;
    }

    case CUP:
    {
        b2CircleShape circle;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        circle.m_radius = 0.475f;
        circle.m_p.Set(0.,0.);
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.4f;
        fixtureDef.filter.maskBits = 0x3;
        fixtureDef.filter.categoryBits = 0x1;
        body->CreateFixture(&fixtureDef);

        radius = circle.m_radius;
        break;
    }

    case STAND:
    {
        b2CircleShape circle;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        circle.m_radius = 0.3f;
        circle.m_p.Set(0.,0.);
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.4f;
        fixtureDef.filter.maskBits = 0x3;
        fixtureDef.filter.categoryBits = 0x1;
        body->CreateFixture(&fixtureDef);

        radius = circle.m_radius;
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
        case GLASS:
        {
            pa.setBrush(p_color);
            pa.setPen(p_color);

            pa.drawEllipse(QPoint(p.x,p.y),40,40);
            break;
		}
        case GIFT:
		{
            pa.setBrush(p_color);
            pa.setPen(p_color);

            pa.drawRect(p.x-75, p.y-25,150,50);
			break;
		}
        case FIREUP:
        {
            pa.translate(QPointF(p.x,p.y));
            pa.rotate(-theta*180/3.14);

            //Dessin:
            //face rouge
            p_color = QColor(204, 6, 5);
            pa.setBrush(p_color);
            pa.setPen(p_color);
            pa.drawRect(0,0,140,-5);

            //milieu noir
            p_color = QColor(10, 10, 10);
            pa.setBrush(p_color);
            pa.setPen(p_color);
            pa.drawRect(0,-5,140,-20);

            //face jaune
            p_color = QColor(250, 210, 1);
            pa.setBrush(p_color);
            pa.setPen(p_color);
            pa.drawRect(0,-25,140,-5);

            pa.rotate(theta*180/3.14);
            pa.translate(QPointF(-p.x,-p.y));
            break;
        }
        case TORCH:
        {
            pa.setBrush(p_color);
            pa.setPen(p_color);

            pa.drawEllipse(QPoint(p.x,p.y),80,80);

            break;
        }
        case CUP:
        {
            pa.setBrush(p_color);
            pa.setPen(p_color);
            pa.setOpacity(0.7);
            pa.drawEllipse(QPoint(p.x,p.y),47.5,47.5);
            pa.setOpacity(1);
            break;
        }
        case STAND:
        {
            pa.setBrush(p_color);
            pa.setPen(p_color);

            pa.drawEllipse(QPoint(p.x,p.y),30,30);
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
