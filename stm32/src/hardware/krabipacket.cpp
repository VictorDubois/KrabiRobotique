#include "krabipacket.h"

#include <string.h>

#ifndef ROBOTHW
#include <QDebug>
#endif

KrabiPacket::KrabiPacket(uint8_t id, W_TABLE watch) : mId(id), mCursor(1), mLength(2), mLengthSecurized(0), mValid(true)
{
    mPacket[0] = mId;

    if (watch != W_NULL)
        add((uint16_t) watch);
}

KrabiPacket::KrabiPacket(uint8_t *data, uint8_t size) : mCursor(1), mLength(0), mLengthSecurized(size)
{
    memcpy(mPacketSecurized, data, mLengthSecurized);

    unsecurize();

    mId = mPacket[0];

    checkValidity();
}

#ifndef ROBOTHW

KrabiPacket::KrabiPacket(QByteArray data) : mCursor(1), mLength(0)
{
#ifdef BLUETOOTH
    uint8_t* array = (uint8_t*)(data.toStdString().c_str());
    mLengthSecurized = data.size();

    memcpy(mPacketSecurized, array, mLengthSecurized);

    unsecurize();

    mId = mPacket[0];

    checkValidity();
#endif
}

QByteArray KrabiPacket::dataByteArray()
{
    QByteArray q((char*) data(), length());

    return q;
}

#endif

bool KrabiPacket::checkValidity()
{
    uint8_t checksum = mPacket[mLength - 1];
    uint8_t computedChecksum = 0;
    for(int i(0); i < mLength - 1; i++)
        computedChecksum += mPacket[i];

    mValid = (checksum == computedChecksum);

#ifndef ROBOTHW
    if (!mValid)
        qDebug() << "ERROR : " << checksum << " != " << computedChecksum;
#endif

    return mValid;
}

bool KrabiPacket::isValid()
{
    return mValid;
}

void KrabiPacket::addData(void* data, uint8_t size)
{
    if (mCursor + size + KRABIPACKET_SUFFIX_SIZE > KRABIPACKET_MAXSIZE)
        return;

    memcpy(mPacket + mCursor, data, size);
    mCursor += size;
    mLength += size;
}

void KrabiPacket::copyData(void* dest, uint8_t size)
{
    if (mCursor + size >= mLength)
        return;

    memcpy(dest, mPacket + mCursor, size);
    mCursor += size;
}

void KrabiPacket::addString(char* data)
{
    int size = 0;
    while( data[size] != '\0' )
        size++;

    addData(data, size + 1);
}

char* KrabiPacket::getString()
{
    char* ptr = (char*)(mPacket + mCursor);
    while( mPacket[mCursor] != '\0' )
        mCursor++;

    return ptr;
}

void KrabiPacket::setId(uint8_t id)
{
    mId = id;
}

uint8_t KrabiPacket::id()
{
    return mId;
}

uint8_t KrabiPacket::length()
{
    securize();
    return mLengthSecurized;
}

void KrabiPacket::securize()
{
    // securize (delete CR + LF)
    mLengthSecurized = 0;
    for(int i(0); i < mLength; i++)
    {
        if (mPacket[i] == 0x0A || mPacket[i] == 0xFF)
            mPacketSecurized[mLengthSecurized++] = 0xFF;
        mPacketSecurized[mLengthSecurized++] = mPacket[i];
    }
}

void KrabiPacket::unsecurize()
{
    mLength = 0;
    for(int i(0); i < mLengthSecurized; i++)
    {
        if (mPacketSecurized[i] == 0xFF)
            i++;
        mPacket[mLength++] = mPacketSecurized[i];
    }
}

uint8_t* KrabiPacket::data()
{
    // checksum
    uint8_t checksum = 0;
    for(int i(0); i < mLength - 1; i++)
        checksum += mPacket[i];
    mPacket[mLength - 1] = checksum;

    securize();

    return mPacketSecurized;
}
