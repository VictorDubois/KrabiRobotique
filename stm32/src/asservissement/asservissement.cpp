#include "asservissement.h"
#include "strategieV2.h"
#include "ascenseur.h"

#include "misc.h"
#include "capteurCouleur.h"

#ifdef REMOTE_ON
    #include "remote.h"
#endif

#define DEBUG_ODOMEDTRIE 1

#define DEBUG_ASSERV 0
#define DEBUG_ASSERV_SIZE 800

#define DEBUG_BLINK_EACH_SECOND 0

#if DEBUG_ASSERV == 1
    //int roueGauche[DEBUG_ASSERV_SIZE];
    //int roueDroite[DEBUG_ASSERV_SIZE];

    float vitesseLin[DEBUG_ASSERV_SIZE];
    float vitesseLinE[DEBUG_ASSERV_SIZE];
    float linearDuty[DEBUG_ASSERV_SIZE];

    float vitesseAng[DEBUG_ASSERV_SIZE];
    float vitesseAngE[DEBUG_ASSERV_SIZE];
    float angularDuty[DEBUG_ASSERV_SIZE];

    float posx[DEBUG_ASSERV_SIZE];
    float posy[DEBUG_ASSERV_SIZE];
    float angle[DEBUG_ASSERV_SIZE];

    uint32_t dbgInc = 0;
#endif

Asservissement * Asservissement::asservissement = NULL; //Pour que nos variables static soient défini
bool Asservissement::matchFini = false;
const uint16_t Asservissement::nb_ms_between_updates = MS_BETWEEN_UPDATE;

Asservissement::Asservissement(Odometrie* _odometrie) /*:
    seuil_collision(SEUIL_COLISION),
    buffer_collision(0xffffffff)*/
{
    vitesseLineaire = 0;
    vitesseAngulaire = 0;
	odometrie = _odometrie;

    activePIDDistance = true;
    activePIDAngle = true;

    resetFixedDuty();

    linearDutySent = 0;
    angularDutySent = 0;
    Asservissement::asservissement = this;
    asserCount = 0;

    nombreQuatumParDixiemeDeSeconde = 1000/(NB_VERIFICATION_BLOQUAGE_PAR_SECONDE*MS_BETWEEN_UPDATE);
    obstacleDetecte = false;
    nbUpdateDepuisObstacleDetecte = 0;
    positionPlusAnglePrecedenteX = 0;
    positionPlusAnglePrecedenteY = 0;
    positionPlusAnglePrecedenteAngle = 0;

    for(int initTableaux = 0 ; initTableaux < NB_VERIFICATION_BLOQUAGE_PAR_SECONDE ; initTableaux++)
    {
        deplacementLineaires[initTableaux] = 0;
        deplacementAngulaire[initTableaux] = 0;
        accelerationLineaires[initTableaux] = 0;
        accelerationAngulaires[initTableaux] = 0;
    }

#ifdef CAPTEURS
    sensors = Sensors::getSensors();
#endif

#ifdef ROBOTHW  //on définie les interruptions possibles dues à certains ports
    *((uint32_t *)(STK_CTRL_ADDR)) = 0x03; // CLKSOURCE:0 ; TICKINT: 1 ; ENABLE:1
#ifdef STM32F40_41xxx
    *((uint32_t *)(STK_LOAD_ADDR)) = 21000*nb_ms_between_updates; // valeur en ms*9000 (doit etre inférieur à 0x00FFFFFF=16 777 215)
#else
    *((uint32_t *)(STK_LOAD_ADDR)) = 9000*nb_ms_between_updates; // valeur en ms*9000 (doit etre inférieur à 0x00FFFFFF=16 777 215)
#endif
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
    vitesseLineaire = vitesse;
    //setEnabledPIDDistance(true);
}

void Asservissement::setAngularSpeed(VitesseAngulaire vitesse)
{
    vitesseAngulaire = vitesse;
    //setEnabledPIDAngle(true);
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

    /*setEnabledPIDDistance(true);
    setEnabledPIDAngle(true);
    resetFixedDuty();*/
}

Distance Asservissement::getLinearSpeed()
{
  /*  if (Remote::getSingleton()->isRemoteMode())
        return Remote::getSingleton()->getLeftPWM();
    else*/
        return vitesseLineaire;
}

Angle Asservissement::getAngularSpeed()
{
   /* if (Remote::getSingleton()->isRemoteMode())
        return Remote::getSingleton()->getRightPWM();
    else*/
        return vitesseAngulaire;
}

void Asservissement::update(void)
{
#ifdef ROBOTHW
    #if DEBUG_ODOMEDTRIE == 1
    PositionPlusAngle pos = Odometrie::odometrie->getPos();
    Angle absAngle = Odometrie::odometrie->getAbsoluteAngle();
    if ( pos.position.x > 400. /* absAngle > 3.14159265358979323846*2.*/)
        Led::setOn(0);
    else
        Led::setOff(0);
    #endif
#endif

    asserCount++;

    if (true)
    {

        PositionPlusAngle positionPlusAngleActuelle = odometrie->getPos();      //Variable juste pour avoir un code plus lisible par la suite
        Angle vitesse_angulaire_atteinte = odometrie->getVitesseAngulaire();    //idem
        Distance vitesse_lineaire_atteinte = odometrie->getVitesseLineaire();   //idem

        //Puis on les récupéres

        float vitesse_lineaire_a_atteindre = getLinearSpeed();
        float vitesse_angulaire_a_atteindre = getAngularSpeed();

        //qDebug() << fixedLinearDuty << " = " << activePIDAngle;

#ifdef ROUES


        //on filtre l'erreur de vitesse lineaire et angulaire
        linearDutySent = activePIDDistance ? pid_filter_distance.getFilteredValue(vitesse_lineaire_a_atteindre-vitesse_lineaire_atteinte) : fixedLinearDuty;
        angularDutySent = activePIDAngle ? pid_filter_angle.getFilteredValue(vitesse_angulaire_a_atteindre-vitesse_angulaire_atteinte) : fixedAngularDuty;

        //Et on borne la somme de ces valeurs filtrée entre -> voir ci dessous
        float limit = 0.5f;

        #ifdef RRD2
            limit = 0.5f;
        #endif


        linearDutySent =  MIN(MAX(linearDutySent, -limit),limit);
        angularDutySent = MIN(MAX(angularDutySent, -limit),limit);

        computeObstacleDetecte(linearDutySent, angularDutySent, &positionPlusAngleActuelle);

        if(obstacleDetecte)
        {
            linearDutySent = 0;
            angularDutySent = 0;
        }

        //On évite que le robot fasse du bruit quand il est à l'arrêt
 //       linearDutySent = fabs(linearDutySent) > 0.05 || vitesse_lineaire_a_atteindre > 0.01 ? linearDutySent : 0;
 //       angularDutySent = fabs(angularDutySent) > 0.05 || vitesse_angulaire_a_atteindre > 0.0001 ? angularDutySent : 0;


        // test d'arret complet si c'est l'ordre qu'on lui donne
        if (vitesse_lineaire_a_atteindre == 0.0f && vitesse_angulaire_a_atteindre == 0.0f)
        {
            linearDutySent = 0.0f;
            angularDutySent = 0.0f;
        }

        // Tourne de façon borné et le fais d'avoir filtrées les valeurs permet de compenser les erreurs
        // passées et de faire tourner chaque roues de façon à tourner et avancer correctement
        /*if (Remote::getSingleton()->isRemoteMode())
        {
            roues.droite.tourne(Remote::getSingleton()->getRightPWM());
            roues.gauche.tourne(Remote::getSingleton()->getLeftPWM());
        }
        else*/
        {
        #if defined(STM32F40_41xxx) || defined(STM32F10X_MD)
            roues.droite.tourne(0.8*MIN(MAX(+linearDutySent-angularDutySent, -limit),limit));
            roues.gauche.tourne(0.8*MIN(MAX(+linearDutySent+angularDutySent, -limit),limit));
        #else
            roues.droite.tourne(0.95*MIN(MAX(+linearDutySent+angularDutySent, -limit),limit));//*1
            roues.gauche.tourne(0.95*MIN(MAX(+linearDutySent-angularDutySent, -limit),limit));//*1
        #endif
        }

        #if DEBUG_ASSERV == 1
        /** Pour afficher les courbes d'asservissement : **/
            if(dbgInc<DEBUG_ASSERV_SIZE)
            {

                int index = dbgInc/4;

                vitesseLin[index] = vitesse_lineaire_atteinte;
                vitesseLinE[index] = vitesse_lineaire_a_atteindre;
                linearDuty[index] = linearDutySent;

                vitesseAng[index] = vitesse_angulaire_atteinte;
                vitesseAngE[index] = vitesse_angulaire_a_atteindre;
                angularDuty[index] = angularDutySent;

                PositionPlusAngle pos = Odometrie::odometrie->getPos();

                posx[index] = pos.position.x;
                posy[index] = pos.position.y;
                angle[index] = pos.angle;

                dbgInc++;

            }
            else
            {

                roues.gauche.tourne(0.0);
                roues.droite.tourne(0.0);
                dbgInc++;

            }
        /** FIN **/
        #endif

    }
    else
    {
        roues.gauche.tourne(0.);
        roues.droite.tourne(0.);
    }
#else
}
#endif
}

#ifdef ROBOTHW
//pour lancer l'update à chaque tic d'horloge
extern "C" void SysTick_Handler()
{
    // Count the number of SysTick_Handler call
    systick_count++;

#if DEBUG_BLINK_EACH_SECOND
    if (systick_count%200 == 0){
        Led::toggle(0);
    }
#endif

    Odometrie::odometrie->update();

    StrategieV2::update();

    Asservissement::asservissement->update();
}

#endif

void Asservissement::finMatch()
{
    Asservissement::matchFini = true;
    #ifdef ROBOTHW


    #endif
}

void Asservissement::setEnabledPIDDistance(bool enabled)
{
    activePIDDistance = enabled;
}

void Asservissement::setEnabledPIDAngle(bool enabled)
{
    activePIDAngle = enabled;
}

void Asservissement::setLinearDuty(float duty)
{
    setEnabledPIDDistance(false);
    fixedLinearDuty = MAX( MIN( duty, FIXED_LINEAR_DUTY_MAX), -FIXED_LINEAR_DUTY_MAX);
}

void Asservissement::setAngularDuty(float duty)
{
    setEnabledPIDAngle(false);
    fixedAngularDuty = MAX( MIN( duty, FIXED_ANGULAR_DUTY_MAX), -FIXED_ANGULAR_DUTY_MAX);
}

void Asservissement::resetFixedDuty()
{
    fixedLinearDuty = 0.;
    fixedAngularDuty = 0.;
}

void Asservissement::computeObstacleDetecte(float linearDutySentArgument, float angularDutySentArgument, PositionPlusAngle* positionPlusAngleActuelleArgument)
{
    //Si on a vu un obstacle recemment
    if(this->obstacleDetecte)
    {
        nbUpdateDepuisObstacleDetecte++;

        //Si ça fait longtemps
        if(nbUpdateDepuisObstacleDetecte > (1000/MS_BETWEEN_UPDATE * 5))//5 secondes
        {
            this->obstacleDetecte = false;
            nbUpdateDepuisObstacleDetecte = 0;
            Asservissement::asservissement->resetAsserv();
        }
    }
    else
    {

        //On ajoute les déplacements élémentaires depuis la dernière boucle
        float variationLineaireX = positionPlusAngleActuelleArgument->position.getX()-positionPlusAnglePrecedenteX;
        float variationLineaireY = positionPlusAngleActuelleArgument->position.getY()-positionPlusAnglePrecedenteY;
        float variationAngulaire = positionPlusAngleActuelleArgument->position.getAngle()-positionPlusAnglePrecedenteAngle;

        //En valeur absolue
        if(variationLineaireX < 0)
        {
            variationLineaireX = -variationLineaireX;
        }
        if(variationLineaireY < 0)
        {
            variationLineaireY = -variationLineaireY;
        }
        if(variationAngulaire < 0)
        {
            variationAngulaire = -variationAngulaire;
        }

        deplacementLineaires[0] += variationLineaireX + variationLineaireY;
        deplacementAngulaire[0] += variationAngulaire;

        positionPlusAnglePrecedenteX = positionPlusAngleActuelleArgument->position.getX();
        positionPlusAnglePrecedenteY = positionPlusAngleActuelleArgument->position.getY();
        positionPlusAnglePrecedenteAngle = positionPlusAngleActuelleArgument->position.getAngle();

        //On ajoute les accélérations élémentaires depuis la dernière boucle
        accelerationLineaires[0]+=linearDutySentArgument;

        accelerationAngulaires[0]+=angularDutySentArgument;

        compteurRemplissageQuatum++;

        //Si ça fait un dixième de seconde, on vérifie qu'on n'est pas bloqué
        if(compteurRemplissageQuatum > nombreQuatumParDixiemeDeSeconde)
        {
            compteurRemplissageQuatum = 0;
            float sommageDeplacementLineaires = 0;
            float sommageDeplacementAngulaire = 0;
            float sommageAccelerationLineaires = 0;
            float sommageAccelerationAngulaires = 0;

            //Sommage des 10 derniers 10èmes
            for(int sommage = 0 ; sommage < NB_VERIFICATION_BLOQUAGE_PAR_SECONDE ; sommage++)
            {
                sommageDeplacementLineaires+=deplacementLineaires[sommage];
                sommageDeplacementAngulaire+=deplacementAngulaire[sommage];
                sommageAccelerationLineaires+=accelerationLineaires[sommage];
                sommageAccelerationAngulaires+=accelerationAngulaires[sommage];
            }

            float accelerationLineaireLimite = ACCELER_LIN_MINIMALE_DETECTION_BLOQUAGE * NB_VERIFICATION_BLOQUAGE_PAR_SECONDE * nombreQuatumParDixiemeDeSeconde;
            float accelerationAngulaireLimite = ACCELER_ANG_MINIMALE_DETECTION_BLOQUAGE * NB_VERIFICATION_BLOQUAGE_PAR_SECONDE * nombreQuatumParDixiemeDeSeconde;

            //Si on accélère à fond en ne bougeant pas plus d'un centimètre en une seconde
//            if(((sommageAccelerationLineaires > accelerationLineaireLimite) && (abs(sommageDeplacementLineaires) < 10)) ||
//               ((sommageAccelerationAngulaires > accelerationAngulaireLimite) && (abs(sommageDeplacementAngulaire) < 3)))

            bool stop = false;

            if(sommageAccelerationLineaires > accelerationLineaireLimite)
            {
                if(sommageDeplacementLineaires < DISTANCE_MINIMALE_DETECTION_BLOQUAGE)
                {
                    stop = true;
                }
            }
            else if(sommageAccelerationAngulaires > accelerationAngulaireLimite)
            {
                if(sommageDeplacementAngulaire < ANGLE_MINIMAL_DETECTION_BLOQUAGE)
                {
                    stop = true;
                }
            }

            if(stop)
            {
                obstacleDetecte = true;
                nbUpdateDepuisObstacleDetecte = 0;

//                //Remise à 0 du tableau
                for(int initTableaux = 0 ; initTableaux < NB_VERIFICATION_BLOQUAGE_PAR_SECONDE ; initTableaux++)
                {
                    deplacementLineaires[initTableaux] = 0;
                    deplacementAngulaire[initTableaux] = 0;
                    accelerationLineaires[initTableaux] = 0;
                    accelerationAngulaires[initTableaux] = 0;
                }
                return;
            }

            //Shift du tableau, les valeurs sont plus vieilles
            for(int raz = NB_VERIFICATION_BLOQUAGE_PAR_SECONDE-1 ; raz > 0 ; raz--)
            {
                deplacementLineaires[raz]=deplacementLineaires[raz-1];
                deplacementAngulaire[raz]=deplacementAngulaire[raz-1];
                accelerationLineaires[raz]=accelerationLineaires[raz-1];
                accelerationAngulaires[raz]=accelerationAngulaires[raz-1];
            }

            //Remise à 0 de la case 1
            deplacementLineaires[0] = 0;
            deplacementAngulaire[0] = 0;
            accelerationLineaires[0] = 0;
            accelerationAngulaires[0] = 0;
        }
    }
    return;
}

void Asservissement::resetAsserv()
{
    pid_filter_distance.resetErrors();
    pid_filter_angle.resetErrors();
}
