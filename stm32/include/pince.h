#ifndef PINCE_H_INCLUDED
#define PINCE_H_INCLUDED

class Robot;

class Pince
{
public:
	Robot* robot;
	Pince(Robot* robot);
	void serrerElem();
	void lacherElem();
	void setLevel();
        unsigned int getLevel();
};

#endif //PINCE_H_INCLUDED
