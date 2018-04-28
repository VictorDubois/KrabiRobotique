
#include "serialCom.h"
#include "serialComStrat.h"
#include "serialMessage.h"
#include <iostream>

//#define SERIAL_COM_DEBUG

SerialComStrat::SerialComStrat() {
    this->serial_com = new SerialCom();
}

SerialComStrat::~SerialComStrat() {
    // Close the Serial Stream.
    delete serial_com;
}

void SerialComStrat::sendMessage(SerialMessage* message) {
    serial_com->sendSerial(message->getType());
    serial_com->sendSerial(message->getLength());
    for(int i=0; i < message->getLength(); i++) {
        serial_com->sendSerial(message->getData()[i]);
    }
}

void SerialComStrat::sendNewMission(PositionPlusAngle position) {
    char messageData[3 * sizeof(uint32_t)];
    for(int i = 0; i < 3 * sizeof(uint32_t); i++) {
        messageData[i] = 0;
    }

    #ifdef SERIAL_COM_DEBUG
    std::cout << std::endl << "initial data" << std::endl;
    std::cout << (uint32_t)position.getPosition().getX() << std::endl;
    std::cout << (uint32_t)position.getPosition().getY() << std::endl;
    std::cout << ((uint32_t)(position.angle+ 360))%360 << std::endl;

    std::cout << std::endl << "getX" << std::endl;
    this->splitToChar((uint32_t)position.getPosition().getX(), messageData);
    for(int i = 0; i < 3 * sizeof(uint32_t); i++) {
        std::cout << (uint32_t)messageData[i] << std::endl;
    }

    std::cout << std::endl << "getY" << std::endl;
    this->splitToChar((uint32_t)position.getPosition().getY(), messageData + sizeof(uint32_t));
    for(int i = 0; i < 3 * sizeof(uint32_t); i++) {
        std::cout << (uint32_t)messageData[i] << std::endl;
    }

    std::cout << std::endl << "angle" << std::endl;
    this->splitToChar(((uint32_t)(position.angle+ 360))%360, messageData + 2*sizeof(uint32_t));
    for(int i = 0; i < 3 * sizeof(uint32_t); i++) {
        std::cout << (uint32_t)messageData[i] << std::endl;
    }
    #else
    this->splitToChar((uint32_t)position.getPosition().getX(), messageData);
    this->splitToChar((uint32_t)position.getPosition().getY(), messageData + sizeof(uint32_t));
    this->splitToChar(((uint32_t)(position.angle+ 360))%360, messageData + 2*sizeof(uint32_t));
    #endif // SERIAL_COM_DEBUG
//    messageData[0] = position->getPosition()->getX() & 0xFF;
//    messageData[1] = 200;

    SerialMessage* message = new SerialMessage(SerialMessage::NEW_MISSION, 3 * sizeof(uint32_t), messageData);
    this->sendMessage(message);
}


/**
 * Split a number to a char array
 * @param uint32_t number the number to convert
 * @param char* message the receiving char array
 */
void SerialComStrat::splitToChar(uint32_t number, char* message) {
    uint8_t length = sizeof(uint32_t);
    uint32_t messageSection;
    for(int iSplit = 0; iSplit < length; iSplit++) {
        messageSection = (number >> (8*iSplit));
        messageSection = messageSection & 0xFF;
        message[iSplit] = messageSection;

        #ifdef SERIAL_COM_DEBUG
        std::cout << "splitToChar: "<< (int32_t)number << \
        " to: " << (uint32_t)message[iSplit] << \
        ", with mask: " << (uint32_t)(0xFF << 8*(iSplit)) \
        << std::endl;
        #endif
    }
//    message[length] = "\n";
}

//char SerialCom::receiveSerial() {
//    char read_byte;
//
//    // Read a character.
//    serial_stream >> read_byte;
//
//    std::cout << "serial_stream read: " << read_byte << std::endl;
//
//    return read_byte;
//}
//
//void SerialCom::sendSerial(char write_byte) {
////    char write_byte_2 = 'b';
//
//    // Write a character.
//    serial_stream << write_byte;
//}

