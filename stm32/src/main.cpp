#include "stm32f10x_gpio.h"
#include "initialisation.h"
#include "memory.h"
#include "servo.h"
#include "odometrie.h"
#include "asservissement.h"
#include "sensors.h"
#include "quadratureCoderHandler.h"
#include "bras.h"
#include "roues.h"
#include "roue.h"
#include "strategieV2.h"
#include "sharpSensor.h"
#include "ax12api.h"
#include "interfaceServosNumeriques.h"
#include "capteurCouleur.h"
#include "tirette.h"
#include "leds.h"
#include "marteaux.h"
#include "commandAllerA.h"

#define POSITIONNEMENT

#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))

// Dit si on est du coté bleu
bool isBlue()
{
#ifdef STM32F10X_MD // Pin pour le stm32 h103
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == Bit_SET;
#endif
#ifdef STM32F10X_CL // Pin pour le stm32 h107
    return GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == Bit_RESET;
#endif
}

// Dit si la tirette est enlevée
bool isTiretteEnlevee()
{
#ifdef STM32F10X_MD // Pin pour le stm32 h103
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_SET;
#endif
#ifdef STM32F10X_CL // Pin pour le stm32 h107
    return GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == Bit_SET;
#endif
}

void initPinPourServoAnalog(GPIO_TypeDef* GPIOx, uint16_t pinX)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pinX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

int main()
{
    *NVIC_CCR = *NVIC_CCR | 0x200; // Set STKALIGN in NVIC

    // On initialise les horloges
    Clk_Init();

    // Définit quelques horloges supplémentaires
    initAutresHorloges();

    // Appel de la fonction qui permet d'initialiser tous les PINS
    initialisationDesPIN();

    ServosNumeriques::initClocksAndPortsGPIO();
    for (int i = 0; i < 10000; i++);
        ServosNumeriques::initUART(1000000);
    for (int i = 0; i < 10000; i++);
        ServosNumeriques::sendMode();

    /******************************************************
    *                 NUMERIC SERVO TEST
    ******************************************************/
    /*while(1)
    {
        // @debug - Servomoteur numérique
        for (int id = 12; id < 13; id++)
        {
            for (int i = 0; i < 10000; i++);
            {
                ServosNumeriques::setLedState(1, id);
                ServosNumeriques::moveToAtSpeed(MBD_ENFONCE, MBD_VITESSE_DESCENTE, id);
            }
        }

        allumerLED();
        for (int i = 0; i < 10000000; i++)
        {}

        for (int id = 12; id < 13; id++)
        {
            for (int i = 0; i < 10000; i++);
            {
                ServosNumeriques::setLedState(0, id);
                ServosNumeriques::moveToAtSpeed(MBD_ENFONCE, MBD_VITESSE_DESCENTE, id);
            }
        }

        eteindreLED();
        for (int i = 0; i < 10000000; i++)
        {}
    }*/


    /*while(1)
    {


        Marteaux::enfoncerBasDroit();
        Marteaux::enfoncerBasGauche();
        Marteaux::enfoncerHautDroit();
        Marteaux::enfoncerHautGauche();
        allumerLED();
        for (int i = 0; i < 6000000; i++)
        {
        }

        eteindreLED();
        Marteaux::releverBasDroit();
        Marteaux::releverBasGauche();
        Marteaux::releverHautDroit();
        Marteaux::releverHautGauche();
        for (int i = 0; i < 6000000; i++)
        {
        }

        Marteaux::enfoncerBasDroit();
        Marteaux::enfoncerBasGauche();
        Marteaux::enfoncerHautDroit();
        Marteaux::enfoncerHautGauche();
        allumerLED();
        for (int i = 0; i < 6000000; i++)
        {
        }

        eteindreLED();
        Marteaux::releverBasDroit();
        Marteaux::releverBasGauche();
        Marteaux::releverHautDroit();
        Marteaux::releverHautGauche();
        for (int i = 0; i < 13000000; i++)
        {
        }

        eteindreLED();
        Marteaux::rangerBasDroit();
        Marteaux::rangerBasGauche();
        Marteaux::rangerHautDroit();
        Marteaux::rangerHautGauche();
        for (int i = 0; i < 10000000; i++)
        {
        }

    }*/

    // test fdc :
    /*
    LimitSwitchSensor* fdc1 = new LimitSwitchSensor(LimitSwitchSensor::BACK_LEFT, GPIO_Pin_14, GPIOD);
    LimitSwitchSensor* fdc2 = new LimitSwitchSensor(LimitSwitchSensor::BACK_RIGHT, GPIO_Pin_1, GPIOD);
    while(1)
    {
        fdc1->updateValue();
        fdc2->updateValue();
        if (fdc1->getValue().b)
            allumerLED();
        else
            eteindreLED();
        if (fdc2->getValue().b)
            allumerLED2();
        else
            eteindreLED2();
        for (int i = 0; i < 10000; i++)
        {
        }
    }*/
    /*
    CapteurCouleur* capteur = new CapteurCouleur(TIM5, GPIOA, GPIO_Pin_0,
                                               GPIOD, GPIO_Pin_0,
                                               GPIOD, GPIO_Pin_2,
                                               GPIOC, GPIO_Pin_8,
                                               GPIOC, GPIO_Pin_10,
                                               GPIOD, GPIO_Pin_7,
                                               GPIOC, GPIO_Pin_12);

    capteur->activerCapteur(GAUCHE_BAS);

    int valeurs[16];

    Tirette tirette(GPIOE, GPIO_Pin_5);
    bool t = true;

    for (int i = 0 ; i < 10000 ; i++)
    {
        if (i % 4 == 0)
        {
            capteur->allumerDiodesRouges(true);
            capteur->allumerDiodesBleues(false);
        }
        else if (i % 4 ==  2)
        {
            capteur->allumerDiodesRouges(false);
            capteur->allumerDiodesBleues(true);
        }
        else
        {
            capteur->allumerDiodesRouges(false);
            capteur->allumerDiodesBleues(false);
        }

        while (true)
        {
            for (int d = 0 ; d < 1000000 ; d++);
            capteur->getTickValue();
            if (tirette.enlevee() == t)
            {
                for (int d = 0 ; d < 1000000 ; d++);
                capteur->selectionnerFiltre(FILTRE_ROUGE);
                valeurs[i*4] = capteur->getTickValue();
                for (int d = 0 ; d < 1000000 ; d++);
                capteur->selectionnerFiltre(FILTRE_VERT);
                valeurs[i*4+1] = capteur->getTickValue();
                for (int d = 0 ; d < 1000000 ; d++);
                capteur->selectionnerFiltre(FILTRE_BLEU);
                valeurs[i*4+2] = capteur->getTickValue();
                for (int d = 0 ; d < 1000000 ; d++);
                capteur->selectionnerFiltre(FILTRE_BLANC);
                valeurs[i*4+3] = capteur->getTickValue();
                t = !t;
                break;
            }

        }
    }*/

    /******************************************************
    *                   SHARP TEST
    ******************************************************/

    /*uint8_t channels[10] = {9,13,8,11,5,10,4,12,14,15};
    uint16_t* data = AnalogSensor::initialiserADC(10, channels);
    int nbSharp = 10;
    SharpSensor** sharps = new SharpSensor*[nbSharp];
    sharps[0] = new SharpSensor(SharpSensor::FRONT_LEFT, 9, data); // front left 9

    // Not working sharp FRONT_RIGHT returns 2800... and is so always on
    sharps[1] = new SharpSensor(SharpSensor::FRONT_RIGHT, 13, data); // front side right 13

    sharps[2] = new SharpSensor(SharpSensor::FRONT_SIDE_LEFT, 8, data); // front side left 8
    sharps[3] = new SharpSensor(SharpSensor::FRONT_SIDE_RIGHT, 11, data); // avant side droite 11
    sharps[4] = new SharpSensor(SharpSensor::BACK_LEFT, 5, data); // ARRIERE gauche 5
    sharps[5] = new SharpSensor(SharpSensor::BACK_MIDDLE, 10, data, 2500.); // back middle 10
    sharps[6] = new SharpSensor(SharpSensor::NONE, 4, data); // arriere droit 4
    sharps[7] = new SharpSensor(SharpSensor::ELEVATOR_TOP, 12, data); // capteur haut ascenseur 12
    sharps[8] = new SharpSensor(SharpSensor::ELEVATOR_DOWN, 14, data); // capteur bas ascenseur 14
    sharps[9] = new SharpSensor(SharpSensor::BACK_RIGHT, 15, data); // rien


    while(1)
    {
        AnalogSensor::startConversion();

        //sharps[SharpSensor::ELEVATOR_TOP]->updateValue();
        for (int i = 0; i < 10; i++)
        {
            if (sharps[i]->getName()!=SharpSensor::FRONT_SIDE_LEFT)
                sharps[i]->updateValue();
        }

        // all tests

        bool on = false;

        for (int i = 0; i < 10; i++)
            if (sharps[i]->getValue().b)
                on = true;

        allumerLED2();

        if (on) {
            allumerLED();
        }
        else {
            eteindreLED();
        }
    }*/

    /*StrategieV2* strat = new StrategieV2();

    while(1)
    {
        strat->update();
        for (int i = 0; i < 1000; i++);
    }*/

    /*GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
    Servo::initPin(GPIOE, GPIO_Pin_9);
    Servo::initPin(GPIOE, GPIO_Pin_11);
    Servo::initPin(GPIOE, GPIO_Pin_13);
    Servo::initPin(GPIOE, GPIO_Pin_14);

    Timer* timer1 = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    Servo* porteGaucheAsc = new Servo(timer1, 1, 0.01f, 0.11f);
    Servo* porteDroiteAsc = new Servo(timer1, 2, 0.01f, 0.11f);
    Servo* porteDroiteBas = new Servo(timer1, 3, 0.01f, 0.11f);
    Servo* porteGaucheBas = new Servo(timer1, 4, 0.02f, 0.14f);


    //Portes* portesAscenseur = new Portes(porteGaucheAsc, porteDroiteAsc, 20.0f, 50.0f, 160.0f, 130.0f);

    while(1)
    {
        for (int i = 0; i < 5000000; i++)
        {
        }

        //porteGaucheAsc->goToAngle(0.0f);
        //porteDroiteAsc->goToAngle(0.0f);
        //porteDroiteBas->goToAngle(0.0f);
        porteGaucheBas->goToAngle(0.0f);
        allumerLED();

        for (int i = 0; i < 5000000; i++)
        {
        }//je vais peut être commencer à adapter le code du robot à ma carte STM32 H103 Krabi Jr 2014

        //porteGaucheAsc->goToAngle(90.0f);
        //porteDroiteAsc->goToAngle(90.0f);
        //porteDroiteBas->goToAngle(90.0f);
        porteGaucheBas->goToAngle(90.0f);
        eteindreLED();

    }*/

    #ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
        Tirette tirette(GPIOA, GPIO_Pin_10);
    #endif
    #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
        Tirette tirette(GPIOE, GPIO_Pin_5);
    #endif

    /*tirette.attendreRemise();
    tirette.attendreEnlevee();*/


    #ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
        QuadratureCoderHandler* rcd = new QuadratureCoderHandler(TIM4, GPIOB, GPIO_Pin_6, GPIOB, GPIO_Pin_7);
        QuadratureCoderHandler* rcg = new QuadratureCoderHandler(TIM1, GPIOA, GPIO_Pin_8, GPIOA, GPIO_Pin_9);
    #endif
    #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
        QuadratureCoderHandler* rcd = new QuadratureCoderHandler(TIM4, GPIOD, GPIO_Pin_12, GPIOD, GPIO_Pin_13);
        GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
        QuadratureCoderHandler* rcg = new QuadratureCoderHandler(TIM3, GPIOA, GPIO_Pin_6, GPIOA, GPIO_Pin_7);
    #endif

    /************************************************
    **             TEST roues codeuses             **
    ************************************************/

    /*int16_t posLeft = 0, posRight = 0;
    while(true)
    {
        posLeft += rcg->getTickValue();     // BreakPoint Here
        posRight += rcd->getTickValue();
    }*/

    /************ FIN TEST roues codeuses ***********/


// Pour la v1 :
//    QuadratureCoderHandler* rcd = new QuadratureCoderHandler(TIM2, GPIOA, GPIO_Pin_0, GPIOA, GPIO_Pin_1);
 //   QuadratureCoderHandler* rcg = new QuadratureCoderHandler(TIM3, GPIOA, GPIO_Pin_6, GPIOA, GPIO_Pin_7);
    Odometrie* odometrie = new Odometrie(rcg, rcd);
    Position pos(1000,1000, isBlue());
    PositionPlusAngle posPlusAngle(pos,0.0f);
    if (!isBlue())
        posPlusAngle = PositionPlusAngle(pos,M_PI);
    odometrie->setPos(posPlusAngle);

    StrategieV2* strat = new StrategieV2(isBlue());//isBlue());
    Asservissement* asserv = new Asservissement(odometrie);  // On définit l'asservissement


    /*CommandAllerA* command = new CommandAllerA(Position(1000,230), false);
    command->update();
    asserv->setCommandSpeeds(command);*/

    while(1);

    return 0;
}

