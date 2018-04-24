#include "serialCom.h"
#include <iostream>

using namespace LibSerial;

SerialCom::SerialCom() {
    // Open the hardware serial ports.
    serial_stream.Open( "/dev/ttyUSB0" );

    // Set the baud rates.
    serial_stream.SetBaudRate( SerialStreamBuf::BAUD_115200 );
}
SerialCom::~SerialCom() {
    // Close the Serial Stream.
    serial_stream.Close();
}

char SerialCom::receiveSerial() {
    char read_byte;

    // Read a character.
    serial_stream >> read_byte;

    std::cout << "serial_stream read: " << read_byte << std::endl;

    return read_byte;
}

void SerialCom::sendSerial(char write_byte) {
//    char write_byte_2 = 'b';

    // Write a character.
    serial_stream << write_byte;
}

