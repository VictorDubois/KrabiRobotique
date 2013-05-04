#include "ax12api.h"

int ax12Checksum(int8_t length, int* parameters)
{
	int checksum = 0;
    for(int i = 0; i < length+1; i++) {
		checksum += parameters[i];
	}
	return (int)(int8_t)(~checksum); // ~ est l'opérateur NOT bit a bit
}
int AX12::getMoveInstruction(int* retour, uint16_t position, uint16_t vitesse, uint8_t servo)
{
    createWriteHeader(retour, servo, 3); // first, we create a write header with 3 more params (for low/height pos and low/height speed)
    retour[5] = AX12_GOAL_POSITION_L;
    retour[6] = (uint8_t)(position);
    retour[7] = (uint8_t)(position>>8);
    retour[8] = (uint8_t)(vitesse);
    retour[9] = (uint8_t)(vitesse>>8);
    retour[10] = ax12Checksum(retour[3], &retour[2]);
    return 11;
}
int AX12::getMoveToInstruction(int* retour, uint16_t position, uint8_t servo)
{
    createWriteHeader(retour, servo, 1); // first, we create a write header with 1 more params (for high position bits)
    retour[5] = AX12_GOAL_POSITION_L;
    retour[6] = (uint8_t)(position);
    retour[7] = (uint8_t)(position>>8);
    retour[8] = ax12Checksum(retour[3], &retour[2]);
    return 9;
}
int AX12::getMoveSpeedInstruction(int* retour, uint16_t vitesse, uint8_t servo)
{
    createWriteHeader(retour, servo, 1); // first, we create a write header with 1 more params (for high speed)
    retour[5] = AX12_MOVING_SPEED_L;
    retour[6] = (uint8_t)(vitesse);
    retour[7] = (uint8_t)(vitesse>>8);
    retour[8] = ax12Checksum(retour[3], &retour[2]);
    return 9;
}
int AX12::getAngleLowerLimitInstruction(int* retour, uint16_t angleLimite, int servo)
{
    createWriteHeader(retour, servo, 1); // first, we create a write header with 1 more params (for low/high angle)
    retour[5] = AX12_CW_ANGLE_LIMIT_L;
    retour[6] = (uint8_t)(angleLimite);
    retour[7] = (uint8_t)(angleLimite>>8); // high bits
    retour[8] = ax12Checksum(retour[3], &retour[2]);
    return 9;
}
int AX12::getAngleUpperLimitInstruction(int* retour, uint16_t angleLimite, int servo)
{
    createWriteHeader(retour, servo, 1); // first, we create a write header with 1 more params (for low/high angle)
    retour[5] = AX12_CCW_ANGLE_LIMIT_L;
    retour[6] = (uint8_t)(angleLimite);
    retour[7] = (uint8_t)(angleLimite>>8); // high bits
    retour[8] = ax12Checksum(retour[3], &retour[2]);
    return 9;
}
int AX12::getTorqueLimitInstruction(int* retour, uint16_t torqueLimite, int servo) // la torque dans la RAM
{
    createWriteHeader(retour, servo, 1); // first, we create a write header with 1 more params (for low/high angle)
    retour[5] = AX12_TORQUE_LIMIT_L;
    retour[6] = (uint8_t)(torqueLimite);
    retour[7] = (uint8_t)(torqueLimite>>8); // high bits
    retour[8] = ax12Checksum(retour[3], &retour[2]);
    return 9;
}
int AX12::getMaxTorqueInstruction(int* retour, uint16_t maxTorque, int servo) // torque dans l'eeprom (pour l'écrire dans la ram au démarrage)
{
    createWriteHeader(retour, servo, 1); // first, we create a write header with 1 more params (for low/high angle)
    retour[5] = AX12_MAX_TORQUE_L;
    retour[6] = (uint8_t)(maxTorque);
    retour[7] = (uint8_t)(maxTorque>>8); // high bits
    retour[8] = ax12Checksum(retour[3], &retour[2]);
    return 9;
}
int AX12::getLedInstruction(int* retour, uint8_t ledOn, int servo)
{
    createWriteHeader(retour, servo, 0); // first, we create a write header with 3 more params (for low/high pos and low/high speed)
    retour[5] = AX12_LED;
    retour[6] = ledOn;
    retour[7] = ax12Checksum(retour[3], &retour[2]);
    return 8;
}
int AX12::getBaudRateInstruction(int* retour, uint8_t baudRate, int servo)
{
    createWriteHeader(retour, servo, 0); // first, we create a write header with 3 more params (for low/high pos and low/high speed)
    retour[5] = AX12_BAUD_RATE;
    retour[6] = baudRate;
    retour[7] = ax12Checksum(retour[3], &retour[2]);
    return 8;
}



void AX12::createWriteHeader(int* retour, int servo, int nombreParamsAjoutes)
{
    retour[0] = 0xff;
    retour[1] = 0xff;
    retour[2] = servo;
    retour[3] = AX12_WRITE_DATA_PARAMS+2+nombreParamsAjoutes;
    retour[4] = AX12_WRITE_DATA;
}
