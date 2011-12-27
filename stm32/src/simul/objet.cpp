#include "simul/objet.h"

Objet::Objet(b2World & world, Position p, Type type)
{
    this->p = p;
    this->type = type;
    theta = 0.;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/100.,p.y/100.);

    body = world.CreateBody(&bodyDef);

    if (type == blackCoin || type == whiteCoin )
    {
        b2CircleShape circle;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        circle.m_radius = 0.6f;
        circle.m_p.Set(0.,0.);
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.4f;
        fixtureDef.filter.maskBits = 0x3;
        fixtureDef.filter.categoryBits = 0x1;
        body->CreateFixture(&fixtureDef);
    }
    else
    {

    }

}

Objet::~Objet()
{
    //dtor
}

void Objet::paint(QPainter &pa)
{
    switch (type)
    {
        case blackCoin:
        {
            pa.setBrush(QBrush(QColor("black")));
            pa.setPen(QBrush(QColor("black")));

            pa.drawEllipse(QPoint(p.x,-p.y),60,-60);
            break;
        }
        case whiteCoin:
        {
            pa.setBrush(QBrush(QColor("white")));
            pa.setPen(QBrush(QColor("white")));

            pa.drawEllipse(QPoint(p.x,-p.y),60,-60);
            break;
        }
        case goldBar:
        {
            pa.setBrush(QBrush(QColor("yellow")));
            pa.setPen(QBrush(QColor("yellow")));

            pa.drawRect(p.x,-p.y,150,-70);
            break;
        }
    }
    return;
}

void Objet::updatePos()
{
    p.x = 100*body->GetPosition().x;
    p.y = 100*body->GetPosition().y;

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
