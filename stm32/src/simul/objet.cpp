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
        circle.m_radius = 0.381f;
        circle.m_p.Set(0.,0.);
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.4f;
        fixtureDef.filter.maskBits = 0x3;
        fixtureDef.filter.categoryBits = 0x1;
        body->CreateFixture(&fixtureDef);

        radius = circle.m_radius;
        break;
    }
    /*case SANDCONE:
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
    case SANDCYLINDER:
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
    }*/

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
    case SANDCUBE1:
    {

    }
    case PORTE:
    {  b2Vec2 vertices[4];
        vertices[0].Set(0.0f, -0.1f);
        vertices[1].Set(0.0f, 0.0f);
        vertices[2].Set(-1.2f, 0.0f);
        vertices[3].Set(-1.2f, -0.1f);

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

        radius = 1.2f;
        break;





    }
    /*case MER:
    { b2Vec2 vertices[4];
        vertices[0].Set(0.0f, -2.32f);
        vertices[1].Set(0.0f, 0.0f);
        vertices[2].Set(-5.1f, 0.0f);
        vertices[3].Set(-5.1f, -2.32f);

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

        radius = 5.1f;
        break;


    }
    case POISSON:
    {
        break;


    }
    case FILET:
    {
        break;


    }*/
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

        pa.drawEllipse(QPoint(p.x,p.y),38.1,38.1);
        break;
    }
/*case SANDCONE:
{    QConicalGradient conicalGradient(QPoint(p.x,p.y), 0);
    conicalGradient.setColorAt(0.2,QColor(232, 140, 0));
    conicalGradient.setColorAt(0.9, Qt::black);
    pa.setBrush(conicalGradient);
    pa.drawEllipse(QPoint(p.x,p.y), 29, 29);
    break;
}*/
case SANDCYLINDER:
{   p_color = QColor(232, 140, 0);
    pa.setBrush(p_color);
    pa.setPen(p_color);
    pa.drawEllipse(QPoint(p.x,p.y),29,29);
    p_color = QColor(0, 0, 0);
    pa.setBrush(p_color);
    pa.setPen(p_color);
    QRectF rectangle(p.x-29, p.y-29,58,58);
        int startAngle = 0 * 16;
        int spanAngle = 360 * 16;
        pa.drawArc(rectangle, startAngle, spanAngle);
    break;
}
    case SANDCUBE:
    {p_color = QColor(232, 140, 0);
    pa.setBrush(p_color);
    pa.setPen(p_color);

    pa.drawRect(p.x, p.y,58,58);
    p_color = QColor(0, 0, 0);
    pa.setBrush(p_color);
    pa.setPen(p_color);
    pa.drawLine(QPointF(p.x, p.y), QPointF(p.x+58, p.y));
    pa.drawLine(QPointF(p.x+58, p.y),QPointF (p.x+58, p.y+58));
    pa.drawLine(QPointF(p.x+58, p.y+58), QPointF(p.x, p.y+58));
    pa.drawLine(QPointF(p.x, p.y+58), QPointF(p.x, p.y));
    break;/*pa.translate(p.x, p.y);
        p_color = QColor(232, 140, 0);
        pa.setBrush(p_color);
        pa.setPen(p_color);
        pa.drawRect(592,842, 58, 58);
        pa.drawRect(650,842, 58, 58);
        pa.drawRect(592,900, 58, 58);
        pa.drawRect(650,900, 58, 58);
        p_color = QColor(0, 0, 0);
        pa.setBrush(p_color);
        pa.setPen(p_color);
        pa.drawLine(QPointF(592,842), QPointF(708,842));
        pa.drawLine(QPointF(592,842), QPointF(592,958));
        pa.drawLine(QPointF(592,958), QPointF(708,958));
        pa.drawLine(QPointF(708,958), QPointF(708,842));
        pa.drawLine(QPointF(650,842), QPointF(650,958));
        pa.drawLine(QPointF(592,900), QPointF(708,900));
        pa.translate(-p.x, -p.y);
        break;*/
    }
    case SANDCUBE1:
    {
      pa.translate(p.x, p.y);
        p_color = QColor(232, 140, 0);
        pa.setBrush(p_color);
        pa.setPen(p_color);
        pa.drawRect(830,0, 58, 58);
        pa.drawRect(888,0, 58, 58);
        pa.drawRect(830,58, 58, 58);
        pa.drawRect(888,58, 58, 58);
        p_color = QColor(0, 0, 0);
        pa.setBrush(p_color);
        pa.setPen(p_color);
        pa.drawLine(QPointF(830,0), QPointF(946,0));
        pa.drawLine(QPointF(946,0), QPointF(946,116));
        pa.drawLine(QPointF(946,116), QPointF(830,116));
        pa.drawLine(QPointF(830,116), QPointF(830,0));
        pa.drawLine(QPointF(888,0), QPointF(888,116));
        pa.drawLine(QPointF(830,58), QPointF(946,58));
        pa.translate(-p.x, -p.y);
        break;
    }
case PORTE:
{
    pa.setBrush(p_color);
    pa.setPen(p_color);
    pa.translate(p.x+240, p.y+0);
     pa.rotate(8);
    pa.drawRect(0, 0, 120, 10);
     pa.rotate(-8);
     pa.translate(300, 0);
    pa.rotate(8);
    pa.drawRect(0, 0, 120, 10);
     pa.rotate(-8);
      pa.translate(-p.x-540, 0);
    break;

}
/*case MER:
{ p_color = QColor(135,206,250);
    pa.setBrush(p_color);
    pa.setPen(p_color);

    pa.drawRect(498,2000, 410, 232);
    pa.drawRect(2110,2000, 410, 232);

    break;



}
case POISSON:
{
    pa.setBrush(p_color);
    pa.setPen(p_color);
    pa.translate(p.x, p.y);
    pa.drawEllipse(0,0,82,50);
    pa.translate(130, 30);
     pa.rotate(80);
   pa.drawEllipse(0,0,82,50);
     pa.translate(130, 40);
    pa.rotate(80);
    pa.drawEllipse(0,0,82,50);
   pa.translate(130, 50);
    pa.rotate(80);
   pa.drawEllipse(0,0,82,50);
     pa.rotate(-240);

   pa.translate(-p.x-390, -p.y-120);
   break;


}
case FILET:
{    pa.translate(p.x, p.y);
    QPen pen;
    pen.setColor(QColor(0, 0, 0));
    QBrush brush(Qt::black);
    brush.setStyle(Qt::Dense5Pattern);
    pa.setPen(pen);
    pa.setBrush(brush);
    pa.drawRect(0, 0, 1144, 232);
     pa.translate(-p.x, -p.y);
     break;

}*/

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
