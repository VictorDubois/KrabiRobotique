
#include "serialCom.h"
#include "serialComStrat.h"
#include "serialMessage.h"
#include <iostream>

//#define SERIAL_COM_DEBUG

/**
 * SerialComStrat's constructor
 */
SerialComStrat::SerialComStrat() {
    this->serial_com = new SerialCom();
}

/**
 * SerialComStrat's constructor
 */
SerialComStrat::~SerialComStrat() {
    // Close the Serial Stream.
    delete serial_com;
}

/**
 * Send a message
 * @param SerialMessage* message the mesage to send
 */
void SerialComStrat::sendMessage(SerialMessage* message) {
    serial_com->sendSerial(message->getType());
    serial_com->sendSerial(message->getLength());
    for(int i=0; i < message->getLength(); i++) {
        serial_com->sendSerial(message->getData()[i]);
    }
}

/**
 * Send a new mission message
 * @param PositionPlusAngle position, the goal to reach
 * @param uint8_t missionType, the type of mission, according to Etape::EtapeType enum
 */
void SerialComStrat::sendNewMission(PositionPlusAngle position, uint8_t missionType) {

    uint8_t length = 3 * sizeof(uint32_t) + sizeof(uint8_t);
    unsigned char messageData[length];
    for(int i = 0; i < length; i++) {
        messageData[i] = 0;
    }

    // Get get X position in the buffer
    this->splitToChar((uint32_t)position.getPosition().getX(), messageData);

    // Get get Y position in the buffer
    this->splitToChar((uint32_t)position.getPosition().getY(), messageData + sizeof(uint32_t));

    // Get get angle in the buffer
    this->splitToChar(((uint32_t)(position.angle+ 360))%360, messageData + 2*sizeof(uint32_t));

    // Get the mission type in the buffer
    messageData[3*sizeof(uint32_t)] = missionType;

    // Send the message
    SerialMessage* message = new SerialMessage(SerialMessage::NEW_MISSION, length, messageData);
    this->sendMessage(message);
}


/**
 * Split a number to an unsigned char array
 * @param uint32_t number the number to convert
 * @param unsigned char* message the receiving unsigned char array
 */
void SerialComStrat::splitToChar(uint32_t number, unsigned char* message) {
    uint8_t length = sizeof(uint32_t);
    uint32_t messageSection;
    for(int iSplit = 0; iSplit < length; iSplit++) {
        messageSection = (number >> (8*iSplit));
        messageSection = messageSection & 0xFF;
        message[iSplit] = (uint8_t)messageSection;

        #ifdef SERIAL_COM_DEBUG
        std::cout << "splitToChar: "<< (int32_t)number << \
        " to: " << (int)message[iSplit] << " " << (int)messageSection << \
        ", with mask: " << (uint32_t)(0xFF << 8*(iSplit)) \
        << std::endl;
        #endif
    }
}


/**
 * Receive a message, and create the message object accordingly
 * @param SerialMessage** message, the pointer that will be filled according to what is received
 */
void SerialComStrat::receiveMessage(SerialMessage** message) {
    unsigned char message_type, message_length;

    message_type = (unsigned char) this->serial_com->receiveSerial();
    std::cout << "message type: " << (uint32_t) message_type << std::endl;

    message_length = (unsigned char) this->serial_com->receiveSerial();
    std::cout << "message length: " << (uint32_t) message_length << std::endl;

    unsigned char message_data[message_length];

    // content
    if(message_length > 0) {
        for(int i = 0; i< message_length; i++) {
            message_data[i] = this->serial_com->receiveSerial();
        }
    }

    std::cout << "message content: "  << std::endl;

    *message = new SerialMessage(message_type, message_length, message_data);
}

