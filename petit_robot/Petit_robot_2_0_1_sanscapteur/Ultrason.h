#ifndef DEF_ULTRASON // Si la constante n'a pas été définie` le fichier n'a jamais été inclus
#define DEF_ULTRASON // On définit la constante pour que la prochaine fois le fichier ne soit plus inclus



#include "Capteur.h"

class Ultrason : public Capteur//Un capteur de distance ultrason est un capteur : héritage !
{
    public:
 
  Ultrason();//Constructeur bidon... Uniquement utilisé pour l'initialisation de detection...
  Ultrason(int capteurPin);
  void Update();//Met à jour la valeur du capteur.
  int VoitQQch();//Renvoie 1 s'il y a un objet suffisament proche.
 
    private:
    
  int distance;//distance à laquelle est l'objet le plus proche.

 
};

#endif
