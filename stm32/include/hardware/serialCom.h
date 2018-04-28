#ifndef SERIALCOM_H
#define SERIALCOM_H

#define USE_SERIAL_PORT
//#define USE_SERIAL_STREAM

#include <SerialPort.h>
#include <SerialStream.h>


using namespace LibSerial;

class SerialCom
{
public:
    unsigned char receiveSerial();
    void sendSerial(unsigned char sendByte);


    SerialCom();
    ~SerialCom();

private:
#ifdef USE_SERIAL_STREAM
    SerialStream serial_stream;
#endif // USE_SERIAL_STREAM
};

#endif // SERIALCOM_H

