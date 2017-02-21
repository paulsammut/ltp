#include <iostream>
#include "ltpclass.h"
#include "ltpmessage.h"

void InputTest(void);

int main(int argc, char *argv[])
{
    std::cout << "Hi fag!"<< std::endl;

    LtpClass ltp1;

    ltp1.InitLtp("/dev/ttyUSB0");
    struct LtpSample sample_temp;

    while(1)
    {
        
        if(ltp1.PollReadLtp(&sample_temp))
            std::cout<< "We have an angle of: " << sample_temp.angle_
                     << " and a distance of " <<  sample_temp.distance_
                     << std::endl;

       // InputTest();
       // ltp1.SendCommand();
    }

    std::cout << "\r\n We shutdown with this code: " << ltp1.Shutdown();
    return 1;
}

void InputTest(void)
{
    int input_c;
    std::cout << " Here are the following options: \r\n"
              << " (0) Spin\r\n"
              << " (1) Position\r\n"
              << " (2) Sweep\r\n"
              << "Enter input: ";

    std::cin >> input_c;

}
