#include <stdint.h>
#include <iostream>
#include "ltpclass.h"
#include "ltpmessage.h"
#include "serialclass.h"


int main(int argc, char *argv[])
{
    std::cout << "Hi!"<< std::endl;

    LtpClass ltp1;

    const char* serialport = "dev/ttyUSB0";
    ltp1.InitLtp(serialport);
    struct LtpSample sample_temp; 

    while(1)
    {
    }
    
    ltp1.Shutdown();
    return 1;
}

int test1(void)
{
    SerialClass my_serial_port;

    my_serial_port.SerialOpen("/dev/ttyUSB0",SerialClass::_B230400);

    uint8_t packet_buffer[255];

    while(1)
    {
        int packet_length = my_serial_port.SerialGetPacket(packet_buffer, 0x00);
        if(packet_length){
            std::cout << "Received a packet! ";
            for(int i = 0; i < packet_length ; i++)
                std::cout << std::hex << (unsigned char)packet_buffer[i] << " ";
            std::cout << std::endl; 
        }
    }
    std::cout << "Closed the serial port with: " << my_serial_port.SerialClose() << std::endl;

    return 1;
}
