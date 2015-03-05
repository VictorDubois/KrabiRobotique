#include "simul/TableGraphics.h"
#include <QDebug>

using namespace std;

Point2d::Point2d(int mx, int my)
{ 
	x = mx; 
	y = my; 
}
void Point2d::addXOffset(int xOffset)
{
	x += xOffset;
}
void Point2d::addYOffset(int yOffset)
{
	y += yOffset;
}
void Point2d::readSelf(XMLTag* tree)
{
	std::vector<XMLTag*> children = tree->getChildren();
	int size = children.size();
	for (int i = 0; i < size; i++)
	{
		QString type = children[i]->getType();
		if (type == "x" || type == "X" || type == "width")
			x = children[i]->getValue().toInt();
		else if (type == "y" || type == "Y" || type == "height")
			y = children[i]->getValue().toInt();
	}
}

Shape::Shape()
{
	p_z = 0;
    solid = false;
}

Shape::~Shape()
{
}

void Shape::setSolid(bool solid)
{
    this->solid = solid;
}

bool Shape::getSolid() const
{
    return solid;
}

void Shape::readSelf(XMLTag* tree)
{
	std::vector<XMLTag*> children = tree->getChildren();
	int size = children.size();
	for (int i = 0; i < size; i++)
	{
		QString type = children[i]->getType();
		if (type == "z" || type == "Z")
			p_z = children[i]->getValue().toInt();
		else if (type == "Color" || type == "color")
			p_color = QColor(children[i]->getValue());
	}
}
void Shape::drawSelf(QPainter* painter)
{
    painter->setBrush(p_color);
    painter->setPen(p_color);
}

void Shape::createSolid(b2Body* body)
{
}

Rect::Rect()
{
	p_start = Point2d();
	p_size = Size2d();
}
Rect::~Rect()
{
}
void Rect::addXOffset(int xOffset)
{
	p_start.addXOffset(xOffset);
}
void Rect::addYOffset(int yOffset)
{
	p_start.addYOffset(yOffset);
}
void Rect::readSelf(XMLTag* tree)
{
	Shape::readSelf(tree); // reads shapes properties
	std::vector<XMLTag*> children = tree->getChildren();
	int size = children.size();
	for (int i = 0; i < size; i++)
	{
		QString type = children[i]->getType();
		if (type == "Position" || type == "position")
			p_start.readSelf(children[i]);
		else if (type == "Size" || type == "size")
			p_size.readSelf(children[i]);
	}
}
void Rect::drawSelf(QPainter* painter)
{
	//Shape::drawSelf(painter);
	painter->fillRect(p_start.x, p_start.y, p_size.x, p_size.y, p_color);
}

void Rect::createSolid(b2Body* body)
{
#ifdef BOX2D_2_0_1
    b2PolygonDef box;
    b2PolygonDef &fixture = box;
#else
    b2PolygonShape box;
    b2FixtureDef fixture;
    fixture.shape = &box;
#endif
    fixture.friction = 0.5;
    fixture.density = 0;

#ifdef BOX2D_2_0_1
#define CreateFixture CreateShape
#endif

    box.SetAsBox(p_size.x/200.,p_size.y/200., b2Vec2((p_start.x + p_size.x/2.)/100.,(p_start.y + p_size.y/2.)/100.),0);
    body->CreateFixture(&fixture);
}
	
RoundedRect::RoundedRect() : Rect()
{
	p_xRadius = 0;
	p_yRadius = 0;
}
void RoundedRect::addXOffset(int xOffset)
{
	Rect::addXOffset(xOffset);
}
void RoundedRect::addYOffset(int yOffset)
{
	Rect::addYOffset(yOffset);
}
void RoundedRect::readSelf(XMLTag* tree)
{
	Rect::readSelf(tree); // reads rect properties
	std::vector<XMLTag*> children = tree->getChildren();
	int size = children.size();
	for (int i = 0; i < size; i++)
	{
		QString type = children[i]->getType();
		if (type == "xradius" || type == "xRadius" || type == "XRadius")
			p_xRadius = children[i]->getValue().toInt();
		else if (type == "yradius" || type == "yRadius" || type == "YRadius")
			p_xRadius = children[i]->getValue().toInt();
		else if (type == "radius" || type == "Radius") 
		{
			p_xRadius = children[i]->getValue().toInt();
			p_yRadius = children[i]->getValue().toInt();
		}
	}
}
void RoundedRect::drawSelf(QPainter* painter)
{
	Shape::drawSelf(painter);
	painter->drawRoundedRect(p_start.x, p_start.y, p_size.x, p_size.y, p_xRadius, p_yRadius);
}

Ellipse::Ellipse()
{
	p_center = Point2d();
	p_xRadius = 0;
	p_yRadius = 0;
}
void Ellipse::addXOffset(int xOffset)
{
	p_center.addXOffset(xOffset);
}
void Ellipse::addYOffset(int yOffset)
{
	p_center.addYOffset(yOffset);
}
void Ellipse::readSelf(XMLTag* tree)
{
	Shape::readSelf(tree); // reads shapes properties
	std::vector<XMLTag*> children = tree->getChildren();
	int size = children.size();
	for (int i = 0; i < size; i++)
	{
		QString type = children[i]->getType();
		if (type == "Center" || type == "center")
			p_center.readSelf(children[i]);
		else if (type == "xradius" || type == "xRadius" || type == "XRadius")
			p_xRadius = children[i]->getValue().toInt();
		else if (type == "yradius" || type == "yRadius" || type == "YRadius")
			p_xRadius = children[i]->getValue().toInt();
		else if (type == "radius" || type == "Radius") 
		{
			p_xRadius = children[i]->getValue().toInt();
			p_yRadius = children[i]->getValue().toInt();
		}
	}
}
void Ellipse::drawSelf(QPainter* painter)
{
	Shape::drawSelf(painter);
	painter->drawEllipse(QPoint(p_center.x, p_center.y), p_xRadius, p_yRadius);
}



TableGraphics::TableGraphics()
{
	shapes.clear();
}

void TableGraphics::addXOffset(int xOffset)
{
	int size = shapes.size();
	for (int i = 0; i < size; i++)
		shapes[i]->addXOffset(xOffset);
}

void TableGraphics::addYOffset(int yOffset)
{
	int size = shapes.size();
	for (int i = 0; i < size; i++)
		shapes[i]->addYOffset(yOffset);
}

void TableGraphics::load(QString filename)
{
	QFile file(filename);
	
	if (!file.open(QIODevice::ReadOnly))
	{
		cout << "Error while opening " << filename.toStdString() << endl;
		return;
	}

	QString text = file.readAll();

	file.close();

	/// NOW PROCESS ALL DATA
	XMLTag* tag = XMLReader::getTree(text); // get the root
	std::vector<XMLTag*> children = tag->getChildren();
	int size = children.size();
	for (int i = 0; i < size; i++)
	{
		QString type = children[i]->getType();
        Shape* shape;
		if (type == "Rect" || type == "rect")
		{
            shape = new Rect();
			shape->readSelf(children[i]);
			shapes.push_back(shape);
		}
		else if (type == "RoundedRect" || type == "roundedrect")
		{
            shape = new RoundedRect();
			shape->readSelf(children[i]);
			shapes.push_back(shape);
		}
        else if (type == "Ellipse" || type == "ellipse")
		{
            shape = new Ellipse();
			shape->readSelf(children[i]);
			shapes.push_back(shape);
		}
        shape->setSolid(children[i]->getSolid());
	}
}

void TableGraphics::draw(QPainter* painter)
{
	int size = shapes.size();
	for (int i = 0; i < size; i++)
		shapes[i]->drawSelf(painter);
}

void TableGraphics::createSolids(b2Body* body)
{
    int size = shapes.size();
    for (int i = 0; i < size; i++)
        if (shapes[i]->getSolid())
            shapes[i]->createSolid(body);
}





