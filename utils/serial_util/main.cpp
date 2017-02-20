#include <iostream>
#include "ltpclass.h"
#include "ltpmessage.h"

int main(int argc, char *argv[])
{
    std::cout << "Hi!"<< std::endl;

    LtpClass ltp1;

    ltp1.InitLtp("/dev/ttyUSB0");
    struct LtpSample sample_temp; 

    while(1)
    {
        if(ltp1.PollReadLtp(&sample_temp))
            std::cout<< "We have an angle of: " << sample_temp.angle_ 
                << " and a distance of " <<  sample_temp.distance_ 
                << std::endl;
    }
    
    std::cout << "\r\n We shutdown with this code: " << ltp1.Shutdown();
    return 1;
}

