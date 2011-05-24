#ifndef PINCE_H_INCLUDED
#define PINCE_H_INCLUDED

#include"Angle.h"
#ifdef ROBOTHW
#include"servo.h"
#endif //ROBOTHW

#ifdef ROBOTHW //vrai robot

class Pince
{
private:
   
    Servo serv1;
    Servo serv2;
   
public:
    Pince(Servo serv1, Servo serv2);
    void pivote(Angle angle);


    //Stub: Should be completed by somebody
	void serrerElem() { }
	void lacherElem() { }
	void setLevel() { }
    unsigned int getLevel() { return 0; }

    ~Pince();

};


#else //simulation

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

#endif //simul
#endif //PINCE_H_INCLUDED
