#include "asservissement.h"
#include "strategieV2.h"
#include "ascenseur.h"
#include "commandAllerA.h"

#include "misc.h"
#include "capteurCouleur.h"

#define DBG_SIZE 750

/* DEBUG AA */
#include "../hardware/leds.h"


#define FREEWHEEL 0


//int roueGauche[DBG_SIZE];
//int roueDroite[DBG_SIZE];

float vitesseLin[DBG_SIZE];
float vitesseLinE[DBG_SIZE];
float linearDuty[DBG_SIZE];

float vitesseAng[DBG_SIZE];
float vitesseAngE[DBG_SIZE];
float angularDuty[DBG_SIZE];

float posX[DBG_SIZE];
float posY[DBG_SIZE];
float posAng[DBG_SIZE];

//float posx[DBG_SIZE];
//float posy[DBG_SIZE];
//float angle[DBG_SIZE];
uint32_t dbgInc = 0;

Command* Asservissement::commandDebugTest = NULL;
int Asservissement::counter = 0;

Asservissement * Asservissement::asservissement = NULL; //Pour que nos variables static soient défini
bool Asservissement::matchFini = false;
const uint16_t Asservissement::nb_ms_between_updates = MS_BETWEEN_UPDATE;

Asservissement::Asservissement(Odometrie* _odometrie) :
    seuil_collision(SEUIL_COLISION),
    buffer_collision(0xffffffff)
{
    vitesseLineaire = 0;
    vitesseAngulaire = 0;
	odometrie = _odometrie;

    linearDutySent = 0;
    angularDutySent = 0;
    Asservissement::asservissement = this;
    asserCount = 0;
#ifdef CAPTEURS
    sensors = Sensors::getSensors();
#endif

#ifdef ROBOTHW  //on définie les interruptions possibles dues à certains ports
    *((uint32_t *)(STK_CTRL_ADDR)) = 0x03; // CLKSOURCE:0 ; TICKINT: 1 ; ENABLE:1
    *((uint32_t *)(STK_LOAD_ADDR)) = 9000*nb_ms_between_updates; // valeur en ms*9000 (doit etre inférieur à 0x00FFFFFF=16 777 215)
    // le micro controlleur tourne à une frequence f (72Mhz ici), la valeur à mettre est (0.001*(f/8))*(temps en ms entre chaque update)
    // voir p190 de la doc

    NVIC_InitTypeDef SysTick_IRQ;

    SysTick_IRQ.NVIC_IRQChannel = SysTick_IRQn;
    SysTick_IRQ.NVIC_IRQChannelCmd = ENABLE;
    SysTick_IRQ.NVIC_IRQChannelPreemptionPriority = 0;
    SysTick_IRQ.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&SysTick_IRQ);
#endif
}

void Asservissement::setLinearSpeed(Vitesse vitesse)
{
    vitesseLineaire = vitesse;//3.5f;
}

void Asservissement::setAngularSpeed(VitesseAngulaire vitesse)
{
    vitesseAngulaire = vitesse;//0.015f;
}

void Asservissement::setCommandSpeeds(Command* command)
{
    if (command != NULL)
    {
        setLinearSpeed(command->getLinearSpeed());
        setAngularSpeed(command->getAngularSpeed());
    }
    else
    {
        setLinearSpeed(0.0f);
        setAngularSpeed(0.0f);
    }
}

Distance Asservissement::getLinearSpeed()
{
    return vitesseLineaire;
}

Angle Asservissement::getAngularSpeed()
{
    return vitesseAngulaire;
}

void Asservissement::update(void)
{
/*
#ifdef CAPTEURS
        AnalogSensor::startConversion(); // On lance la conversion des données que l'on reçois des capteurs pour les avoir au bon moment
#endif
*/
    asserCount++;
/*
#ifdef ROUES
    //On arrete le robot pour être sur que tout soit réinitialisé
    if(asserCount > CPT_BEFORE_RAZ)
    {
        roues.gauche.tourne(0);
        roues.droite.tourne(0);
    }
#endif*/


    if (1/*asserCount< 85000/MS_BETWEEN_UPDATE && !Asservissement::matchFini*/)
    {

        PositionPlusAngle positionPlusAngleActuelle = odometrie->getPos();      //Variable juste pour avoir un code plus lisible par la suite
        Angle vitesse_angulaire_atteinte = odometrie->getVitesseAngulaire();    //idem
        Distance vitesse_lineaire_atteinte = odometrie->getVitesseLineaire();   //idem

#ifdef ROUES
/*
#ifdef CAPTEURS
    bool testcap = sensors->detectedSharp()->getSize() > 0;
#else

    bool testcap = false;
#endif*/

/*if (testcap)
{
    Command::freinageDUrgence(true);
  //  linearDutySent = 0;
  //  angularDutySent = 0;
}
else
    Command::freinageDUrgence(false);*/
#endif //ROUES

        //Puis on les récupéres

        float vitesse_lineaire_a_atteindre = getLinearSpeed();
     //   vitesse_lineaire_a_atteindre += ACCELERATION_LINEAIRE_MAX;
     //   vitesse_lineaire_a_atteindre = (vitesse_lineaire_a_atteindre >= 4.0) ? 4.0f : vitesse_lineaire_a_atteindre;
        float vitesse_angulaire_a_atteindre = getAngularSpeed();
      //     vitesse_angulaire_a_atteindre += ACCELERATION_ANGULAIRE_MAX;
     //   vitesse_angulaire_a_atteindre = (vitesse_angulaire_a_atteindre >= VITESSE_ANGULAIRE_MAX) ? VITESSE_ANGULAIRE_MAX : vitesse_angulaire_a_atteindre;
//vitesse_angulaire_a_atteindre = (vitesse_angulaire_a_atteindre <= -VITESSE_ANGULAIRE_MAX) ? -VITESSE_ANGULAIRE_MAX : vitesse_angulaire_a_atteindre;

        // le buffer de collision se vide si l'accélération demandé est trop forte. Normalement la commande vérifie ça.
 /*       //Il faudrai qu'il passe de marche arriére à marche avant à toute vitesse pour avoir une collision ...
        buffer_collision <<= 1;
        buffer_collision |= fabs((vitesse_lineaire_atteinte - vitesse_lineaire_a_atteindre)) < seuil_collision && fabs((vitesse_angulaire_atteinte - vitesse_angulaire_a_atteindre)) < SEUIL_COLISION_ANG;
*/
#ifdef ROUES


        //on filtre l'erreur de vitesse lineaire et angulaire
        linearDutySent = pid_filter_distance.getFilteredValue(vitesse_lineaire_a_atteindre-vitesse_lineaire_atteinte);
        angularDutySent = pid_filter_angle.getFilteredValue(vitesse_angulaire_a_atteindre-vitesse_angulaire_atteinte);

        //Et on borne la somme de ces valeurs filtrée entre -> voir ci dessous
        float limit = 1.0f;
        linearDutySent =  MIN(MAX(linearDutySent, -limit),limit);
        angularDutySent = MIN(MAX(angularDutySent, -limit),limit);

        //On évite que le robot fasse du bruit quand il est à l'arrêt
 //       linearDutySent = fabs(linearDutySent) > 0.05 || vitesse_lineaire_a_atteindre > 0.01 ? linearDutySent : 0;
 //       angularDutySent = fabs(angularDutySent) > 0.05 || vitesse_angulaire_a_atteindre > 0.0001 ? angularDutySent : 0;


        // test d'arret complet si c'est l'ordre qu'on lui donne
        /*if (vitesse_lineaire_a_atteindre == 0.0f && vitesse_angulaire_a_atteindre == 0.0f)
        {
            linearDutySent = 0.0f;
            angularDutySent = 0.0f;
        }*/

        limit = 1.0f;
        float rapportLeft = 1.0*MIN(MAX(+linearDutySent-angularDutySent, -limit),limit);
        float rapportRight = 1.0*MIN(MAX(+linearDutySent+angularDutySent, -limit),limit);


        if (FREEWHEEL/*buffer_collision == 0x0 */)//|| GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)  == Bit_RESET) //Actif si le buffer_de colision est vide.
        {   //Si on détecte quelque chose, on s'arréte

            roues.gauche.tourne(0.);
            roues.droite.tourne(0.);
        }
        else
        {   //Sinon les roues tourne de façon borné et le fait d'avoir filtrées les valeurs permet de compenser les erreurs passées et de faire tournées chaque roues de façon
            // à tourner et avancer correctement
            limit = 0.4f;

            roues.gauche.tourne(rapportLeft);
            roues.droite.tourne(rapportRight);
        }


        // Pour afficher les courbes :
            if(dbgInc<DBG_SIZE)
            {

                vitesseLin[dbgInc] = vitesse_lineaire_atteinte;
                vitesseLinE[dbgInc] = vitesse_lineaire_a_atteindre;
                linearDuty[dbgInc] = linearDutySent;

                vitesseAng[dbgInc] = vitesse_angulaire_atteinte;
                vitesseAngE[dbgInc] = vitesse_angulaire_a_atteindre;
                angularDuty[dbgInc] = angularDutySent;

                if (StrategieV2::currentCommand!=0)
                {
                    posX[dbgInc] = ((CommandAllerA*)(StrategieV2::currentCommand))->_angleVise;//positionPlusAngleActuelle.position.x;
                    posY[dbgInc] = ((CommandAllerA*)(StrategieV2::currentCommand))->_angleLimit;//positionPlusAngleActuelle.position.y;
                }
                else
                {
                    posX[dbgInc] = -1.;//positionPlusAngleActuelle.position.x;
                    posY[dbgInc] = -1.;//positionPlusAngleActuelle.position.y;
                }

                posAng[dbgInc] = positionPlusAngleActuelle.angle;

                dbgInc++;

            }
            else
            {

                roues.gauche.tourne(0.0);
                roues.droite.tourne(0.0);
                dbgInc++;
                roues.gauche.tourne(0.0);
                roues.droite.tourne(0.0);
            }
        // Courbes - fin


    }
    else
    {
        roues.gauche.tourne(0.0);
        roues.droite.tourne(0.0);
    }
#else
}
#endif
}

#ifdef ROBOTHW
// allume ou éteint une LED
void xallumerLED()
{
#ifdef STM32F10X_MD // stm32 h103
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
#endif
#ifdef STM32F10X_CL // stm32 h107
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET); // LED verte
#endif
}

void xeteindreLED()
{
#ifdef STM32F10X_MD // stm32 h103
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
#endif
#ifdef STM32F10X_CL // stm32 h107
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET); // LED verte
#endif
}

// 2ème LED du stm h107 (LED jaune)
#ifdef STM32F10X_CL
void xallumerLED2()
{
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
}
void xeteindreLED2()
{
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
}
#endif

#endif

int currentTimer = 0;
//PositionPlusAngle posOdo;

#ifdef ROBOTHW
//pour lancer l'update à chaque tic d'horloge
extern "C" void SysTick_Handler()
{
/*
   static Roue* ascensseur = NULL;
   if (ascensseur==NULL)
        ascensseur = new Roue(TIM5, 3, GPIOA, GPIO_Pin_2, GPIOD, GPIO_Pin_5);

    if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == Bit_SET)
        ascensseur->tourne(-1.0f);
    else
        ascensseur->tourne(1.0f);
*/

    Odometrie::odometrie->update();

    //currentTimer++;
#ifdef ROBOTHW
    /*float xx = Odometrie::odometrie->getPos().angle;

    if (xx>1050.)
    {
        allumerLED();
        //currentTimer = 0;
    }
    else
        eteindreLED();*/
#endif

    /*Asservissement::counter++;
    if (Asservissement::counter>100)
    {
        allumerLED();
        if (Asservissement::counter>200)
            Asservissement::counter = 0;
    }
    else
        eteindreLED();*/

/*#ifdef CAPTEURS
    Sensors* sensors = Sensors::getSensors();
    if (sensors != NULL)
        sensors->update();
#endif
*/
  StrategieV2::update();

  /*Asservissement::commandDebugTest->update();
  if (Asservissement::commandDebugTest->fini())
  {
      Asservissement::asservissement->setAngularSpeed(0.);
      Asservissement::asservissement->setLinearSpeed(0.);
  }
  else
   Asservissement::asservissement->setCommandSpeeds(Asservissement::commandDebugTest);*/

   /*if (StrategieV2::strategie != NULL)
    StrategieV2::strategie->update();*/

  Asservissement::asservissement->update();


/*
    static int i = 0;

    if (i % 200 == 0)
    {
    //    ascensseur->tourne(0.9f);
    //    Asservissement::asservissement->roues.gauche.tourne(0.7f);
    //    Asservissement::asservissement->roues.droite.tourne(-0.5f);
        xeteindreLED();
        xallumerLED2();

    }
    else if (i % 100 == 0)
    {
  //      ascensseur->tourne(-0.7f);
   //     Asservissement::asservissement->roues.gauche.tourne(-0.5f);
   //     Asservissement::asservissement->roues.droite.tourne(0.8f);
        xallumerLED();
        xeteindreLED2();

    }
    i++;
*/

    /*Ascenseur* ascenseur = Ascenseur::get();
    if (ascenseur != NULL)
        ascenseur->update();*/

/*
if (Odometrie::odometrie->ang < 0.2*3.1415/180.0 && Odometrie::odometrie->ang > -0.2*3.1415/180.0)
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
    }
*/
/*
   Odometrie::odometrie->update();
   if (Odometrie::odometrie->posX > -5000.0)
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
    }
    else if (Odometrie::odometrie->posX < -5000.0)
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
    }
*/

/*
    static CapteurCouleur* c = NULL;
    static int seuilMax = 200;
    static int seuilMin = 120;

    if (c == NULL)
        c = new CapteurCouleur(TIM2, GPIOA, GPIO_Pin_6);

    static uint16_t ticks[DBG_SIZE];
    static int nbBoucles = 0;

    if (nbBoucles % 200 == 100)
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
    if (nbBoucles % 200 == 199)
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);*/

/*
    uint16_t nbTicks = c->getTickValue();

    if (nbTicks > seuilMax)
        xallumerLED2();
    else
        xeteindreLED2();

    if (nbTicks < seuilMin)
        xallumerLED();
    else
        xeteindreLED();*/
/*
    if (nbBoucles < DBG_SIZE)
    {

        ticks[nbBoucles] = c->getTickValue();
        nbBoucles++;
    }
    else
    {
        nbBoucles++;
    }
*/
}

#endif

void Asservissement::finMatch()
{
    Asservissement::matchFini = true;
    #ifdef ROBOTHW


    #endif
}
