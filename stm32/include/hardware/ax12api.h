#ifndef AX12API_H_INCLUDED
#define AX12API_H_INCLUDED

// EEPROM memory addresses
#define AX12_MODEL_NUMBER_L 		0x00
#define AX12_MODEL_NUMBER_H 		0x01
#define AX12_FIRMWARE_VERSION 		0x02
#define AX12_ID 					0x03
#define AX12_BAUD_RATE 				0x04
#define AX12_RETURN_DELAY_TIME 		0x05
#define AX12_CW_ANGLE_LIMIT_L 		0x06
#define AX12_CW_ANGLE_LIMIT_H 		0x07
#define AX12_CCW_ANGLE_LIMIT_L 		0x08
#define AX12_CCW_ANGLE_LIMIT_H 		0x09
#define AX12_HIGHEST_TEMPERATURE 	0x0B
#define AX12_LOWEST_VOLTAGE 		0x0C
#define AX12_HIGHEST_VOLTAGE 		0x0D
#define AX12_MAX_TORQUE_L 			0x0E
#define AX12_MAX_TORQUE_H 			0x0F
#define AX12_STATUS_RETURN_LEVEL 	0x10
#define AX12_ALARM_LED 				0x11
#define AX12_ALARM_SHUTDOWN 		0x12
#define AX12_DOWN_CALIBRATION_L 	0x14
#define AX12_DOWN_CALIBRATION_H 	0x15
#define AX12_UP_CALIBRATION_L 		0x16
#define AX12_UP_CALIBRATION_H 		0x17

// RAM addresses
#define AX12_TORQUE_ENABLE 			0x18
#define AX12_LED 					0x19
#define AX12_CW_COMPLIANCE_MARGIN 	0x1A
#define AX12_CCW_COMPLIANCE_MARCHIN 0x1B
#define AX12_CW_COMPLIANCE_SLOPE	0x1C
#define AX12_CCW_COMPLIANCE_SLOPE	0x1D
#define AX12_GOAL_POSITION_L 		0x1E
#define AX12_GOAL_POSITION_H		0x1F
#define AX12_MOVING_SPEED_L			0x20
#define AX12_MOVING_SPEED_H			0x21
#define AX12_TORQUE_LIMIT_L			0x22
#define AX12_TORQUE_LIMIT_H			0x23
#define AX12_PRESENT_POSITION_L		0x24
#define AX12_PRESENT_POSITION_H		0x25
#define AX12_PRESEND_SPEED_L		0x26
#define AX12_PRESENT_SPEED_H		0x27
#define AX12_PRESENT_LOAD_L			0x28
#define AX12_PRESENT_LOAD_H			0x29
#define AX12_PRESENT_VOLTAGE		0x2A
#define AX12_PRESENT_TEMPERATURE	0x2B
#define AX12_REGISTERED_INSTRUCTION 0x2C
#define AX12_MOVING					0x2E
#define AX12_LOCK					0x2F
#define AX12_PUNCH_L				0x30
#define AX12_PUNCH_H				0x31

// Instructions values and parameters count
#define AX12_PING 					0x01
#define AX12_PING_PARAMS			0
#define AX12_READ_DATA 				0x02
#define AX12_READ_DATA_PARAMS		2
#define AX12_WRITE_DATA 			0x03
#define AX12_WRITE_DATA_PARAMS 		2
#define AX12_REG_WRITE 				0x04
#define AX12_REG_WRITE_PARAMS 		2
#define AX12_ACTION 				0x05
#define AX12_ACTION_PARAMS 			0
#define AX12_RESET 					0x06
#define AX12_RESET_PARAMS 			0
#define AX12_SYNC_WRITE 			0x83
#define AX12_SYNC_WRITE_PARAMS 		4

#include "memory.h"
#include <stdint.h>

/** Calcul de la checksum d'un paquet
 * Un paquet envoyé au ax12 est 0xFF 0xFF ID length param1 ... paramN checksum
 * Où la checksum vaut ~(ID+length+param1+...+paramN) avec ~ l'opérateur not
 * On tronque aux 8 bits de poids faible.
 *
 * \brief Calcule la checksum d'un paquet envoyé au ax12
 * \param length nombre de paramètres envoyés
 * \param parameters paramètres envoyés au ax12
 *
*/
int ax12Checksum(int8_t length, int* parameters);

struct AX12ReturnPacket
{
    int header1;
    int header2;
    int servo;
    int length;
    int error;
    int* parameter;
    int checksum;
};

class AX12
{
    public:

    static int getMoveInstruction(int* retour, uint16_t position = 0x00, uint16_t vitesse = 0x02, uint8_t servo = 0xfe);
    static int getMoveToInstruction(int* retour, uint16_t position = 0x00, uint8_t servo = 0xfe);
    static int getMoveSpeedInstruction(int* retour, uint16_t vitesse = 0x02, uint8_t servo = 0xfe);
    static int getAngleLowerLimitInstruction(int* retour, uint16_t angleLimite = 0, int servo = 0xfe);
    static int getAngleUpperLimitInstruction(int* retour, uint16_t angleLimite = 0, int servo = 0xfe);
    static int getTorqueLimitInstruction(int* retour, uint16_t torqueLimite = 0, int servo = 0xfe); // la torque dans la RAM
    static int getMaxTorqueInstruction(int* retour, uint16_t maxTorque = 0, int servo = 0xfe); // torque dans l'eeprom (pour l'écrire dans la ram au démarrage)
    static int getLedInstruction(int* retour, uint8_t ledOn = 0, int servo = 0xfe);

    private:

    static void createWriteHeader(int* retour, int servo = 0xfe, int nombreParamsAjoutes = 0);

};


#endif






