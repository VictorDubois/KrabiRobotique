
#include "serialMessage.h"
#include <iostream>


SerialMessage::SerialMessage(uint8_t type, uint8_t length, char* data) {
    this->type = type;
    this->length = length;

    this->data = data;
}

SerialMessage::~SerialMessage() {

}

uint8_t SerialMessage::getType() {
    return this->type;
}

uint8_t SerialMessage::getLength() {
    return this->length;
}

char* SerialMessage::getData() {
    return this->data;
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

