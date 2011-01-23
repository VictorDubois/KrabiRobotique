#ifndef RATEAU_H_INCLUDED
#define RATEAU_H_INCLUDED

#include"Angle.h"
#include"servo.h"


class Rateau
{
 private:

 Servo serv1;
 Servo serv2;

 public:
 Rateau(Servo serv1, Servo serv2);
 void pivote(Angle angle);
 ~Rateau();

};

#endif // RATEAU_H_INCLUDED
