#include "ltpclass.h"
#include "serialclass.h"
#include <iostream>
#include <math.h>

#ifndef PI
#define PI 3.14159265
#endif

extern "C"
{
#include "cobs.h"
}

uint16_t LtpClass::Init(const char *port_name, double head_phi_radians=(PI/2))
{
    //char port[] = "/dev/ttyUSB0";
    std::cout << "Program Loaded!" << std::endl;

    if(ltp_serial_port_.SerialOpen(port_name, SerialClass::_B230400) < 0)
        return 0;

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

    // Copy the struct by value
    *sample1 = *(struct LtpSample*)tempBuff;
    return 1;
}

int16_t LtpClass::PollRead(LtpHitXyz *ltp_hit_xyz)
{
    LtpSample ltp_sample;
    // Do a serial read
    int packet_length = ltp_serial_port_.SerialGetPacket(packet_buffer_,0x00);
    if(packet_length)
    {
        // This means that we got a byte array from the serial read.
        if(DecodePacket(packet_buffer_, packet_length,&ltp_sample))
        {
            // Convert the ltp_sample to a LtpHitXyz
            ConvToXyz(&ltp_sample, ltp_hit_xyz);
            return 1;
        }
    }
    // packet read failed
    return 0;
}

int LtpClass::ConvToXyz(const struct LtpSample *ltp_sample, LtpHitXyz *ltp_hit_xyz)
{
    // Reverse the angle to work with the LTP_Body reference frame
    double reversed = 3999 -ltp_sample->angle_;
    // convert to radians.
    double head_angle_theta = reversed / 3999 * PI * 2;
    // convert distance to meters from centimeteres
    double distance_rho = ((double)ltp_sample->distance_) / 100;

    // std::cout << "Distance: " << ltp_sample->distance_
    //     << " Angle: " << ltp_sample->angle_
    //     << std::endl;

    // Calculate cartesian coordinates
    ltp_hit_xyz->hitpos_x = distance_rho * sin(head_angel_phi_) * cos(head_angle_theta);
    ltp_hit_xyz->hitpos_y = distance_rho * sin(head_angel_phi_) * sin(head_angle_theta);
    ltp_hit_xyz->hitpos_z = distance_rho * cos(head_angel_phi_);



    return 1;
}

int LtpClass::SendCommand(struct LtpCommand *input_ltpcommand)
{
    // here we encode the command in cobs and then it to through the serial bus.

    static uint8_t *temp_ltpcommand;
    static uint8_t temp_encoded[255];
    static int temp_encoded_length;
    static int write_return = 0;

    // get the size of our byte array
    static int temp_cmd_length = sizeof(*input_ltpcommand);

    // Make sure our string is not too long
    if(temp_cmd_length> 251)
        return 0;

    // make our byte array hold the address of the command struct
    temp_ltpcommand = (uint8_t*)input_ltpcommand;

    // encode the command string
    temp_encoded_length = cobs_encode(temp_ltpcommand, temp_cmd_length, temp_encoded);

    if(temp_encoded_length && temp_encoded_length < 255)
    {
        // This means we successfully encoded this string and it is not too long
        // Terminate our string with a zero and increment our length
        temp_encoded[temp_encoded_length++] = 0;
        write_return = ltp_serial_port_.SerialWrite(temp_encoded, temp_encoded_length);
    }


    return write_return;
}


void LtpClass::PrintHit(LtpHitXyz *ltp_hit_xyz)
{
    std::cout <<  " X: " << ltp_hit_xyz->hitpos_x
            << " Y: " << ltp_hit_xyz->hitpos_y
            << " Z: " << ltp_hit_xyz->hitpos_z
            << "\r";
}

int16_t LtpClass::Shutdown(void)
{
    return ltp_serial_port_.SerialClose();
}


