#include "Calibration.h"
#include "CommandReculer.h"
#include "Sensors.h"
#include "odometrie.h"
#include "CommandGoTo.h"

void Calibration::calibrerZeroX()
{
    CommandReculer* command = new CommandReculer();

    Sensors* sensors = Sensors::getSensors();

    bool b = sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_LEFT);
    bool c = sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_RIGTH);

    while(!sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_LEFT) || !sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_RIGTH))
    {}
    b = sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_LEFT);
    c = sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_RIGTH);

    delete command;

    Odometrie::setX(75);
    Odometrie::setAngle(0);

}

void Calibration::calibrerMaxX()
{
    CommandReculer* command = new CommandReculer();

    Sensors* sensors = Sensors::getSensors();

    while(!sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_LEFT) || !sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_RIGTH))
    {}

    delete command;

    Odometrie::setX(3000-75);
    Odometrie::setAngle(M_PI);
}

void Calibration::calibrerZeroY()
{
    bool cote = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)  == Bit_SET ? 1 : -1;
    CommandReculer* command = new CommandReculer();

    Sensors* sensors = Sensors::getSensors();

    while(!sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_LEFT) || !sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_RIGTH))
    {}

    delete command;

    Odometrie::setY(75);
    Odometrie::setAngle(cote*M_PI_2);
}


void Calibration::calibrerMaxY()
{
    bool cote = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)  == Bit_SET ? 1 : -1;
    CommandReculer* command = new CommandReculer();

    Sensors* sensors = Sensors::getSensors();

    while(!sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_LEFT) || !sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_RIGTH))
    {}

    delete command;

    Odometrie::setX(2000-75);
    Odometrie::setAngle(-cote*M_PI_2);
}

void Calibration::calibrationInitial()
{
    bool cote = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)  == Bit_SET ? 1 : -1;

    Calibration::calibrerZeroX();

    new CommandGoTo(Position(900.,Odometrie::odometrie->getPos().getPosition().getY()));

    while((Odometrie::odometrie->getPos().getPosition()-Position(900,Odometrie::odometrie->getPos().getPosition().getY())).getNorme()> DISTANCE_ARRET)
    {}

    new CommandGoTo(Position(900.,cote* (Odometrie::odometrie->getPos().getPosition().getY()+300.)));

    while((Odometrie::odometrie->getPos().getPosition()-Position(900,cote* (Odometrie::odometrie->getPos().getPosition().getY()+300.))).getNorme()> DISTANCE_ARRET)
    {}

    Calibration::calibrerZeroY();
}
