
#ifndef SERIALCOMSTRAT_H
#define SERIALCOMSTRAT_H

#include "serialCom.h"
#include "serialMessage.h"
#include "positionPlusAngle.h"

class SerialComStrat
{
public:
    void sendMessage(SerialMessage* message);
    void sendNewMission(PositionPlusAngle position);
//    void sendSerial(char sendByte);

    SerialComStrat();
    ~SerialComStrat();


    /** @brief types of packets */
    enum PacketType
    {
        ASK_NEXT_MISSION = 0x01,
        OBSTACLE_DETECTED = 0x02,
        NEW_MISSION = 0x03,
        ACK = 0x04,
        NACK = 0x05
    };

private:
    SerialCom* serial_com;
    void splitToChar(uint32_t, char*);

};

#endif // SERIALCOMSTRAT_H

