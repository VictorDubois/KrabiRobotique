#include "serialCom.h"
#include <iostream>

#ifndef USE_SERIAL_PORT
//#define USE_SERIAL_PORT
#endif

#define SERIAL_OUTPUT_DEBUG

//#ifndef USE_SERIAL_STREAM
//#define USE_SERIAL_STREAM
//#endif

using namespace LibSerial;

#ifdef USE_SERIAL_PORT
SerialPort* serial_port = new SerialPort("/dev/ttyUSB0");
#endif // USE_SERIAL_PORT

SerialCom::SerialCom() {
#ifdef USE_SERIAL_STREAM
    // Open the hardware serial ports.
    serial_stream.Open( "/dev/ttyUSB0" );

    // Set the baud rates.
    serial_stream.SetBaudRate( SerialStreamBuf::BAUD_115200 );
#endif // USE_SERIAL_STREAM
#ifdef USE_SERIAL_PORT
    // Open the hardware serial ports.
    serial_port->Open(SerialPort::BAUD_115200, SerialPort::CHAR_SIZE_8, SerialPort::PARITY_DEFAULT, SerialPort::STOP_BITS_DEFAULT, SerialPort::FLOW_CONTROL_DEFAULT);
#endif // USE_SERIAL_PORT
}
SerialCom::~SerialCom() {
#ifdef USE_SERIAL_STREAM
    // Close the Serial Stream.
    serial_stream.Close();
#endif // USE_SERIAL_STREAM
#ifdef USE_SERIAL_PORT
    serial_port->Close();
#endif // USE_SERIAL_PORT
}

unsigned char SerialCom::receiveSerial() {
    unsigned char read_byte = 0;

#ifdef USE_SERIAL_STREAM
    // Read a character.
    serial_stream >> read_byte;
#endif // USE_SERIAL_STREAM
#ifdef USE_SERIAL_PORT
    while(!serial_port->IsDataAvailable()) {
    }
    read_byte = serial_port->ReadByte();
#endif // USE_SERIAL_PORT
    return read_byte;
}

void SerialCom::sendSerial(unsigned char write_byte) {
#ifdef USE_SERIAL_STREAM
    // Write a character.
    serial_stream << write_byte;
    std::cout << (uint32_t)write_byte << std::endl;
#endif // USE_SERIAL_STREAM
#ifdef USE_SERIAL_PORT
    serial_port->WriteByte(write_byte);

    #ifdef SERIAL_OUTPUT_DEBUG
    std::cout << (uint32_t)write_byte << std::endl;
    #endif // SERIAL_OUTPUT_DEBUG
#endif // USE_SERIAL_PORT
}

