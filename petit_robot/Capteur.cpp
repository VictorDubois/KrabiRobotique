#include "Capteur.h"
#include "Arduino.h"
#include "Sharp.h"
#include "Ultrason.h"

Capteur::Capteur(int capteurPin) : capteurPin(capteurPin), valeur(0)
{
  //capteurPin = capteurPin;
  //valeur = 0;
}

Capteur::Capteur(int capteurPin, int valeur) : capteurPin(capteurPin), valeur(valeur)
{
  //capteurPin = capteurPin;
  //valeur = 0;
}

Capteur::~Capteur()
{

}

int Capteur::GetValue()
{
  Update();
  return valeur;
}

void Capteur::Update()
{
  
}
