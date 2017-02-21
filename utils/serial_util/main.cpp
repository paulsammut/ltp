#include <iostream>
#include "ltpclass.h"
#include "ltpmessage.h"

void InputTest(void);
LtpClass ltp1;

void PrintBanner(void)
{
    std::cout 
        << "============================\r\n"
        << "=SAMMUT-TECH-LLC============\r\n"
        << "=cybernetics-division=======\r\n"
        << "============================\r\n"
        << "===== LTP Test Program =====\r\n"
        << "============================"<< std::endl;
}

int main(int argc, char *argv[])
{
    PrintBanner();

    ltp1.InitLtp("/dev/ttyUSB0");
    struct LtpSample sample_temp;
    struct LtpCommand test_command;
    test_command.cmdtype_ = MSG_SPIN;
    test_command.param1_= 70;
    test_command.param2_= 0x24;
    test_command.param3_= 0x30;

    while(1)
    {
       /* 
        if(ltp1.PollReadLtp(&sample_temp))
            std::cout<< "We have an angle of: " << sample_temp.angle_
                     << " and a distance of " <<  sample_temp.distance_
                     << std::endl;
*/
        PrintBanner();
        InputTest();
    }

    std::cout << "\r\n We shutdown with this code: " << ltp1.Shutdown();
    return 1;
}

void InputTest(void)
{
    struct LtpCommand cmd_from_input;
    int input_c;
    std::cout << " Here are the following options: \r\n"
              << " (0) Spin\r\n"
              << " (1) Position\r\n"
              << " (2) Sweep\r\n"
              << " (3) Quit\r\n"
              << "Enter input: ";

    std::cin >> input_c;

    switch(input_c){
        case 0:
            std::cout << "Please enter speed from -100 to 100: ";
            int speed;
            std::cin >> speed;
            cmd_from_input.cmdtype_ = MSG_SPIN;
            cmd_from_input.param1_ = speed;
            ltp1.SendCommand(&cmd_from_input);
            break;

        case 1:
            std::cout << "Please enter an angle from 0-4000 (maps to 0-360 degrees): ";
            int pos;
            std::cin >> pos;
            cmd_from_input.cmdtype_ = MSG_POSITION;
            cmd_from_input.param1_ = pos;
            ltp1.SendCommand(&cmd_from_input);
            break;

        case 2:
            cmd_from_input.cmdtype_ = MSG_SWEEP;

            std::cout << "Enter start sweep pos (0-360): ";
            double pos_start;
            std::cin >> pos_start;
            cmd_from_input.param2_ = (int16_t)(pos_start/360*4000);

            std::cout << "Enter end sweep pos (0-360): ";
            double pos_end;
            std::cin >> pos_end;
            cmd_from_input.param1_ = (int16_t)(pos_end/360*4000);

            std::cout << "Enter frequency (0-40): ";
            double freq;
            std::cin >> freq;
            cmd_from_input.param3_ = (int16_t)(freq*10); 

            ltp1.SendCommand(&cmd_from_input);
            break;

        case 3:
            ltp1.Shutdown();
            exit(0);
    }
}
