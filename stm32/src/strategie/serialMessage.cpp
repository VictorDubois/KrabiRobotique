#include "serialMessage.h"
#include <iostream>

/**
 * SerialMessage's constructor
 */
SerialMessage::SerialMessage(uint8_t type, uint8_t length, unsigned char* data) {
    this->type = type;
    this->length = length;
    this->data = data;
}

/**
 * SerialMessage's destructor
 */
SerialMessage::~SerialMessage() {

}

/**
 * Returns the message's type, according to SerialMessage::PacketType
 * @return uint8_t the message's type
 */
uint8_t SerialMessage::getType() {
    return this->type;
}

/**
 * Returns the message's data
 * @return uint8_t the message's data length
 */
uint8_t SerialMessage::getLength() {
    return this->length;
}

/**
 * Returns the message's data
 * @return unsigned char* the message's data
 */
unsigned char* SerialMessage::getData() {
    return this->data;
}
