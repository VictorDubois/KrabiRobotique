#ifndef CONSTANTE_H
#define CONSTANTE_H

enum MOVE_KIND{MOVE_NONE, DELAY, DISABLE_SHARPS, ENABLE_SHARPS, MOVE_FORWARD, MOVE_BACKWARD, MOVE_45CLOCK, MOVE_45ANTICLOCK};
enum SHARP_PLACE{SHARP_FRONT_L, SHARP_FRONT_R, SHARP_FRONT_C, SHARP_BEHIND};

#endif // CONSTANTE_H


/*
// DEFINITION DES CONSTANTES //

const int pinRoueG = 5;
const int pinRoueD = 3;



const int pinCalClaire = 9;
const int pinCalObs = 7;
const int pinCalGD = 6;

//##### Arduino nano
const int pinCCG = A0;//pin du CapteurCouleurGauche
const int pinCCD = A7;

const int pinTirr = A2;

const int pinSharpAvG = A1;//attention, aussi défini dans detection
const int pinSharpAvD = A3;
const int pinSharpArr = A6;

const int pinLed1 = 8;
const int pinLed2 = 11;
const int pinLed3 = 12;

const int pinPing = 10;

enum couleurMatch { ROUGE, VIOLET };
enum sharpDetectant { AUCUN, GAUCHE, DROITE, TTAVANT, ARRIERE, TTGAUCHE, TTDROITE, TT,  AUCUNETHAUT, GAUCHEETHAUT, DROITEETHAUT, TTAVANTETHAUT, ARRIEREETHAUT, TTGAUCHEETHAUT, TTDROITEETHAUT, TTETHAUT,  AUCUNETMILIEU, GAUCHEETMILIEU, DROITEETMILIEU, TTAVANTETMILIEU, ARRIEREETMILIEU, TTGAUCHEETMILIEU, TTDROITEETMILIEU, TTETMILIEU,  AUCUNETHAUTETMILIEU, GAUCHEETHAUTETMILIEU, DROITEETHAUTETMILIEU, TTAVANTETHAUTETMILIEU, ARRIEREETHAUTETMILIEU, TTGAUCHEETHAUTETMILIEU, TTDROITEETHAUTETMILIEU, TTETHAUTETMILIEU};
enum sens { AVANCER, RECULER, TOURNEGAUCHE, TOURNEDROITE, AVANCERBOUTEILLE };

int couleurRobot = 0;

//  PARAMETRES DE DEPLACEMENT AUTOMATIQUE //

const unsigned long dureeMatch = 89000;// 89 secondes : mieux vaut ne pas prendre de risques
//const unsigned long dureeMatch = 9000;// 89 secondes : mieux vaut ne pas prendre de risques
unsigned long tempDepartMatch = 0;

const int paramArretRoueG = 90;
const int paramArretRoueD = 90;


const int TTDroitRoueG = 110;
const int TTDroitRoueD = 69;//70à

const int TournerGaucheRoueG = 82;
const int TournerGaucheRoueD = 82;
const int TournerGaucheTemps = 865;

const int TournerDroiteRoueG = 98;
const int TournerDroiteRoueD = 98;
const int TournerDroiteTemps = 865;

const int ReculerRoueG = 77;
const int ReculerRoueD = 110;

const int ReculerLentRoueG = 85;
const int ReculerLentRoueD = 95;







const unsigned long tempsMaxCapteurs = 10;

//  PARAMETRES DE SUIVEUR DE LIGNE //

const int valMoyenneG = 0;
const int valMoyenneD = 0;

//pour lancer le rattrapa(ge
int seuilHautRattrapageG = 0;
int seuilHautRattrapageD = 0;
int seuilBasRattrapageG = 0;
int seuilBasRattrapageD = 0;

int basGauche=0;
int basDroite=0;
int hautGauche=0;
int hautDroite=0;

int seuilHautDifferenceRattrapageG=0;
int seuilHautDifferenceRattrapageD=0;

const int paramDiff = 2;

const int paramD = 0;
const int paramG = 0;

const int offsetD = 0;
const int offsetG = 0;

const float paramSeuilHautRattrapage = 0.99;
const float paramSeuilBasRattrapage = 1.003;


//pour arreter le rattrppage
const int tempMaxRattrappage = 1000;

int seuilHautRattrapeeG = 0;
int seuilHautRattrapeeD = 0;
int seuilBasRattrapeeG = 0;
int seuilBasRattrapeeD = 0;

const float paramSeuilHautRattrapee = 0.8;
const float paramSeuilBasRattrapee = 1.1;

//  PARAMETRES DES SHARPS //

const int distanceMin = 15;





// DEFINITION DES VARIBABLES //

int bouteilleUneAPousser=0;
int utiliseLigne=0;


// VARIABLES DIODES //
Diode diode1(pinLed1), diode2(pinLed2), diode3(pinLed3);
Detection detection;



int cycleAllumeDiode1 = 0;//Nombre de cycle de boucle pendant lesquels la diode 1 doit etre allumée : permet d'avoir des diodes allumées pendant des cycles entiers, pour qu'elles soient suffisament lumineuses.
int cycleAllumeDiode2 = 0;
int cycleAllumeDiode3 = 0;
*/
