#include "Calibration.h"
#include "CommandReculer.h"
#include "Sensors.h"
#include "odometrie.h"
#include "CommandGoTo.h"

void Calibration::calibrerZeroX()
{
    CommandReculer* command = new CommandReculer();

    Sensors* sensors = Sensors::getSensors();

    while(sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_LEFT) && sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_RIGTH))
    {}

    delete command;

    Odometrie::setX(75);

}

void Calibration::calibrerMaxX()
{
    CommandReculer* command = new CommandReculer();

    Sensors* sensors = Sensors::getSensors();

    while(sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_LEFT) && sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_RIGTH))
    {}

    delete command;

    Odometrie::setX(3000-75);
}

void Calibration::calibrerZeroY()
{
    CommandReculer* command = new CommandReculer();

    Sensors* sensors = Sensors::getSensors();

    while(sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_LEFT) && sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_RIGTH))
    {}

    delete command;

    Odometrie::setY(75);
}


void Calibration::calibrerMaxY()
{
    CommandReculer* command = new CommandReculer();

    Sensors* sensors = Sensors::getSensors();

    while(sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_LEFT) && sensors->detectedLimitSwitch(LimitSwitchSensor::BACK_RIGTH))
    {}

    delete command;

    Odometrie::setY(2000-75);
}

void Calibration::calibrationInitial()
{
    bool cote = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)  == Bit_SET ? 1 : -1;

    Calibration::calibrerZeroX();

    new CommandGoTo(Position(900.,cote* POS_DEPART_Y));

    while((Odometrie::odometrie->getPos().getPosition()-Position(900,cote*POS_DEPART_Y)).getNorme()< 300)
    {}

    new CommandGoTo(Position(900.,cote* (POS_DEPART_Y+300.)));

    while((Odometrie::odometrie->getPos().getPosition()-Position(900,cote* (POS_DEPART_Y+300.))).getNorme()< 300)
    {}

    Calibration::calibrerZeroY();
}
