
#ifdef STM32F40_41xxx
    #include "stm32f4xx_gpio.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_gpio.h"
#endif

#include "servo.h"

#ifdef ROBOTHW

// on donne le rapport cyclique de l'angle minimal (0 degré) et celui de l'angle maximal (180 degrés)
Servo::Servo(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres)
    : pwm_handler(timer, OCx), m_timer(timer), m_RC0degre(RC0degre), m_coefRC((RC180degres-RC0degre)/180.0f)
{
}

Servo::~Servo()
{
    shutDownServo();
}

// initialise la pin du servo
void Servo::initPin(GPIO_TypeDef* GPIOx, uint16_t pinX)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pinX;

    #ifdef STM32F40_41xxx
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    #endif
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void Servo::goToAngle(Angle angle)
{
/*	// Convertir angle en signal
	// ANGLETOPULSE(a)    (a*500)/124+1500
	// float pulseWidth = ANGLETOPULSE(angle);
	if (angle < 0.0f)
        angle = 0.0f;
    else if (angle > 180.0f)
        angle = 180.0f;
	float pulseWidth = angle*19.5f+1200.0f; // pour le servo ES 539 made in malaysia

    // Donner la rapport au PWM
	pwm_handler.setPulseWidth(pulseWidth);*/

    if (angle < 0.0)
        angle = 0.0f;
    else if (angle > 180.0f)
        angle = 180.0f;

    float rc = m_RC0degre + m_coefRC * angle;
	pwm_handler.setDutyCycle(rc);
}

void Servo::shutDownServo()
{
    pwm_handler.setPulseWidth(0);
}

//void Servo::initTimer()
//{

	// frequence_impulsion = 50Hz : Une impulsion toutes les 20ms
	// frequence_timer = 1Mhz : Précision de 1us -> 1000 positions possible -> précision de 0.18°
	// timPrescaler = 72e6/(frequence_timer*valeur_timClockDivision)-1
    // timPeriod = frequence_timer/frequence_impulsion
 //   timer = new Timer(numero_timer, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
//}

//Timer *Servo::timer = NULL;


#endif // ROBOTHW
