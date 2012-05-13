#ifndef DEF_SHARP // Si la constante n'a pas été définie` le fichier n'a jamais été inclus
#define DEF_SHARP // On définit la constante pour que la prochaine fois le fichier ne soit plus inclus


#include "Capteur.h"

class Sharp : public Capteur//Un sharp est un capteur : héritage !
{
    public:
    
  Sharp();
  Sharp(int capteurPin, int seuil);
  void Update();//Met à jour la valeur du capteur.
  int VoitQQch();//Renvoit 1 si le capteur voie qqch (d'après seuil), 0 sinon.

 
    private:
    
  int seuilDetection;
 
};

#endif
