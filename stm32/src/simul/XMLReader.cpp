#include "simul/XMLReader.h"
#include <QDebug>

using namespace std;

XMLTag::XMLTag() 
{
	p_parent = NULL;
	p_children.clear();
	p_type = "";
	p_inside = "";
	p_value = "";
    p_solid = false;
}

QString XMLTag::convertInsideValuesToTags(QString values)
{
	QString ret = "";
	while (values.size() > 0)
	{
		// removes spaces
		int textStartPos = values.indexOf(' ');
		while (textStartPos == 0)
		{
			values = values.right(values.size() - 1);
			textStartPos = values.indexOf(' ');
		}
		if (values.size() == 0)
			return ret;
		// now read the tag
		int endOfTag = values.indexOf('=');
		QString tag = values.left(endOfTag);
	
		// keep only what's after tag.
		values = values.right(values.size() - endOfTag - 1);
	
		// removes spaces
		textStartPos = values.indexOf(' ');
		while (textStartPos == 0)
		{
			values = values.right(values.size() - 1);
			textStartPos = values.indexOf(' ');
		}
		// get the integers representing a value
		bool isInQuotes = (values.at(0) == '"');
		if (isInQuotes) values = values.right(values.size() - 1);
		int endOfValue = 0;
		if (isInQuotes)
			endOfValue = values.indexOf('"');
		else {
			endOfValue = values.indexOf(' ');
			if (endOfValue == -1) // {val=3} this kind of case
			{
				endOfValue = values.size();
				values = values+" "; // add a character for the end
			}
		}
		
		// now get the value
		QString valOfTag = values.left(endOfValue);	
		ret += "<"+tag+">"+valOfTag+"</"+tag+">";
		// clear the value from what we've read
		values = values.right(values.size() - endOfValue - 1);
	}
	return ret;
}
void XMLTag::print()
{
	int size = p_children.size();
	for (int i = 0; i<size; i++)
	{
		p_children[i]->print();
	}
}
		
QString XMLTag::readSelf(QString input)
{
	// first step : read the first tag
	int posStart = input.indexOf('<');
	if (posStart < 0)	
		return input;
	QString partial = input.right(input.size() - (posStart+1));
	int posEnd = partial.indexOf('>');
	if (posEnd < 0)	
		return input;
	
	bool isLonely = (partial.at(posEnd-1) == '/');
	// now we're sure we've read a tag	
	if (isLonely) // we've got a lonely tag 
		partial = partial.left(posEnd-1); // {<mytag value="" blabla=3/>} looks like {mytag value="" blabla=3} now
	else // no lonely tag
		partial = partial.left(posEnd);

    QString searchSolid = "solid=\"1\"";//Pour activer les collision avec le décors : "solid=\"1\"", sinon "solid=\"0\"";
    bool isSolid = partial.mid(posEnd - searchSolid.length(), searchSolid.length()) == searchSolid;
    if(isSolid)
        setSolid(true);

    int nameEnd = partial.indexOf(' ');
	if (nameEnd < 0) // no spaces, {myType} tag
	{
		setType(partial);
		partial = "";
	}
	else // spaces, {<myType [otherstuff]>} tag
	{
		setType(partial.left(nameEnd));	
		partial = partial.right(partial.size() - nameEnd - 1);
	}
	// now partial looks like {otherstuff} or is empty
	QString converted = convertInsideValuesToTags(partial);
	p_inside = converted;

	// If we had a lonely tag, it's the end.
	if (isLonely) return input.right(input.size() - input.indexOf('>') - 1);

	// reinitialises partial :
	partial = converted + input.right(input.size() - input.indexOf('>') - 1);

	// Now we have to detect the end tag.
	int opened = 0;
	bool started = false; // did we start to read a tag ?
	bool opening = false; // what's the current tag doing : opening a new object or closing one ?
	int i = 0;
	int cuttingPos = 0;
	while (opened >= 0)
	{	
		if (partial.at(i) == '<')
		{
			if (partial.at(i+1) == '/')
				opening = false;
			else
				opening = true;
			started = true;
			cuttingPos = i;
		}
		else if (partial.at(i) == '>' && started)
		{
			if (partial.at(i-1) == '/')
			{
				if (opening == false) // </ /> tag : means nothing
					return input;
			}
			else 
			{
				if (opening) 
					opened++;
				else
					opened--;
			}
			started = false;
		}
		i++;
	}
	// it ends : i is where stops the current tag.
	p_inside = partial.left(cuttingPos);

	return partial.right(partial.size()-i); //, input.size()-(posEnd+1)-(input.size()-lastPos));
}

		
void XMLTag::readInside()
{
	while (p_inside != "")
	{
		XMLTag* tag = new XMLTag();
		QString before = p_inside;
		p_inside = tag->readSelf(p_inside); // read one tag
		if (p_inside == before) // we read a prop value
		{
			p_value = p_inside;
			p_inside = "";
		}
		if (!tag->finishedReading())
			tag->readInside();
		tag->setParent(this);
		if (tag->getType() != "")
			p_children.push_back(tag); // add it to children
		else
			delete tag;
	}
}

void XMLTag::setSolid(bool solid)
{
    p_solid = solid;
}

void XMLTag::setType(QString type)
{
	p_type = type;
}
void XMLTag::setValue(QString value)
{
	p_value = value;
}
void XMLTag::setParent(const XMLTag* tag)
{
	p_parent = tag;
}
void XMLTag::addChild(XMLTag* tag)
{
	p_children.push_back(tag);
}
void XMLTag::setInside(QString inside)
{
	p_inside = inside;
}

const bool& XMLTag::getSolid() const
{
    return p_solid;
}
const QString& XMLTag::getType() const
{
	return p_type;
}
const QString& XMLTag::getValue() const
{
	return p_value;
}
const XMLTag* XMLTag::getParent()
{
	return p_parent;
}
std::vector<XMLTag*> XMLTag::getChildren()
{
	return p_children;
}
bool XMLTag::finishedReading() const
{
	return (p_inside.size() == 0);
}

/*********************************************************************
					XML READER NAMESPACE
**********************************************************************/




namespace XMLReader
{
	XMLTag* getTree(QString xmlString)
	{
		XMLTag* tag = new XMLTag();
		tag->setType("ROOT");
		tag->setValue("");
		tag->setInside(xmlString);
		tag->readInside();
		return tag;
	}
}




