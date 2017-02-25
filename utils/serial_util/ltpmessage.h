#ifndef LTP_MESSAGE_H
#define LTP_MESSAGE_H

/**
 * @file ltpmessge.h
 * @brief Defines the communications between the LTP and the computer
 * @author Paul Sammut
 * @version 1
 * @date 2017-02-18
 */
#include <stdint.h>

/**
 * @brief the message type 
 */
enum LtpCommandType {
    MSG_STOP,
    MSG_SPIN,
    MSG_POSITION,
    MSG_SWEEP
};

/**
 * @brief The LTPMessage struct containing a type and 3 parameters
 */
struct LtpCommand
{
    uint8_t cmdtype_;
    int16_t param1_;
    int16_t param2_;
    int16_t param3_;
};

/**
 * @brief This message is sent by the LTP to the computer. It contains a sample of
 * data with the angle and distance of the LIDAR hit. Angle is 0-4000 and distance is
 * in centimeters.
 */
struct LtpSample
{
    uint16_t distance_;
    uint16_t angle_;
};

#endif /* LTP_MESSAGE_H */
