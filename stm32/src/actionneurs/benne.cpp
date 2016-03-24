#include "benne.h"

#ifdef ROBOTHW
    #include "interfaceServosNumeriques.h"
#else
    #include <QDebug>
#endif

#include "hardware/microSwitch.h"

Benne* Benne::getInstance()
{
    static Benne* instance = 0;
    if(!instance)
        instance = new Benne();
    return instance;
}

Benne::Benne()
{
    #ifdef ROBOTHW
        m_backSwitch    = new MicroSwitch(GPIOE, GPIO_Pin_3);
        m_frontSwitch   = new MicroSwitch(GPIOE, GPIO_Pin_2);
    #else
        m_backSwitch    = new MicroSwitch();
        m_frontSwitch   = new MicroSwitch();
    #endif

    isBenneEmpty = true;

    m_status = Status::UNKNOWN;

    #ifdef ROBOTHW
        ServosNumeriques::changeContinuousRotationMode(BELTS_SERVO_ID, true);

        ServosNumeriques::changeContinuousRotationMode(RAMP_LEFT_SERVO_ID,  false);
        ServosNumeriques::changeContinuousRotationMode(RAMP_RIGHT_SERVO_ID, false);
    #endif
}

Benne::~Benne()
{
    delete m_backSwitch;
    delete m_frontSwitch;
}

void Benne::setBenneEmpty() {
    isBenneEmpty = true;
}

void Benne::setBenneFull() {
    isBenneEmpty = false;
}

bool Benne::getIsBenneEmpty() const
{
    return isBenneEmpty;
}

bool Benne::getIsBenneFull() const
{
    return !isBenneEmpty;
}

Benne::Status::Enum Benne::getStatus() const
{
    return m_status;
}

void Benne::setStatus(Status::Enum status)
{
    m_status = status;
}

void Benne::empty()
{
    if(getStatus() != Status::CLOSED && getStatus() != Status::CLOSING)
    {
        #ifdef ROBOTHW
            ServosNumeriques::moveAtSpeed(FORWARD_SPEED, BELTS_SERVO_ID);
        #else
            qDebug() << "Bin is closing";
        #endif
        setStatus(Status::CLOSING);
    }
}

void Benne::open()
{
    if(getStatus() != Status::OPEN && getStatus() != Status::OPENING)
    {
        #ifdef ROBOTHW
            ServosNumeriques::moveAtSpeed(BACKWARD_SPEED, BELTS_SERVO_ID);
        #else
            qDebug() << "Bin is opening";
        #endif
        setStatus(Status::OPENING);
    }
}

void Benne::deployRamp()
{
    #ifdef ROBOTHW
        ServosNumeriques::moveTo(RAMP_LEFT_DEPLOYED_ANGLE,  RAMP_LEFT_SERVO_ID);
        ServosNumeriques::moveTo(RAMP_RIGHT_DEPLOYED_ANGLE, RAMP_RIGHT_SERVO_ID);
    #else
        qDebug() << "Deploying ramp";
    #endif
}

void Benne::retractRamp()
{
    #ifdef ROBOTHW
        ServosNumeriques::moveTo(RAMP_LEFT_RETRACTED_ANGLE,  RAMP_LEFT_SERVO_ID);
        ServosNumeriques::moveTo(RAMP_RIGHT_RETRACTED_ANGLE, RAMP_RIGHT_SERVO_ID);
    #else
        qDebug() << "Retracting ramp";
    #endif
}

void Benne::update()
{
    if(getStatus() == Status::CLOSING && isFrontSwitchActive())
    {
        stop();
        setStatus(Status::CLOSED);
        setBenneEmpty();

        #ifndef ROBOTHW
            qDebug() << "Bin is closed";
        #endif
    }
    else if(getStatus() == Status::OPENING && isBackSwitchActive())
    {
        stop();
        setStatus(Status::OPEN);

        #ifndef ROBOTHW
            qDebug() << "Bin is open";
        #endif
    }
}

void Benne::stop()
{
    #ifdef ROBOTHW
        ServosNumeriques::moveAtSpeed(0, BELTS_SERVO_ID);
    #endif
}

bool Benne::isFrontSwitchActive() const
{
    return m_frontSwitch->ferme();
}

bool Benne::isBackSwitchActive() const
{
    return m_backSwitch->ferme();
}
