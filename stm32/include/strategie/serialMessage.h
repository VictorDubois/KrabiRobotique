
#ifndef SERIALMESSAGE_H
#define SERIALMESSAGE_H

#include "serialCom.h"

class SerialMessage
{
public:
    SerialMessage(uint8_t type, uint8_t length, unsigned char* data);
    ~SerialMessage();

    uint8_t getType();
    uint8_t getLength();
    unsigned char* getData();


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
    uint8_t type;
    uint8_t length;
    unsigned char* data;
};

#endif // SERIALMESSAGE_H

