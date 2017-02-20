#include "ltpclass.h"
#include "serialclass.h"
#include <iostream>

extern "C"
{
#include "cobs.h"
}

uint16_t LtpClass::InitLtp(const char *port_name)
{
    //char port[] = "/dev/ttyUSB0";
    std::cout << "Program Loaded!" << std::endl;

    if(ltp_serial_port_.SerialOpen(port_name, SerialClass::_B230400) < 0)
        return 0;

    ltp_serial_port_.SerialRead(packet_buffer_, 128, true);
    return 1;
}


uint16_t LtpClass::DecodePacket(
    const uint8_t *raw_packet,
    size_t raw_packet_length,
    struct LtpSample *sample1)
{

    uint8_t tempBuff[255];
    size_t tempBuffLength;
    // Make sure the packet is not longer than the limit
    // and that the end of the raw packet has the 0 terminator
    if(raw_packet_length >= 254 || raw_packet[raw_packet_length-1] != 0x00)
        return 0;

    // we decrement rawPacketLength to get rid of the trailing zero
    --raw_packet_length;

    tempBuffLength = cobs_decode(raw_packet, raw_packet_length, tempBuff);

    if(!tempBuffLength)
    {
        return 0;
    }

    *sample1 = *(struct LtpSample*)tempBuff;
    return 1;
}

int16_t LtpClass::PollReadLtp(struct LtpSample *ltp_sample)
{
    // Do a serial read
    int packet_length = ltp_serial_port_.SerialGetPacket(packet_buffer_,0x00);
    if(packet_length)
    {
        // This means that we got a byte array from the serial read.
        if(DecodePacket(packet_buffer_, packet_length,ltp_sample))
            return 1;
    }

    // packet read failed
    return 0;
}

int16_t LtpClass::Shutdown(void)
{
    return ltp_serial_port_.SerialClose();
}



