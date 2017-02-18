#ifndef LTP_MESSAGE_H
#define LTP_MESSAGE_H

/**
 * @file LTPmessge.h
 * @brief Defines the communications between the LTP and the computer
 * @author Paul Sammut
 * @version 1
 * @date 2017-02-18
 */
#include <stdint.h>

/**
 * @brief the message type 
 */
enum LTPCommandType {
    MSG_STOP,
    MSG_SPIN,
    MSG_POSITION,
    MSG_SWEEP
};

/**
 * @brief The LTPMessage struct containing a type and 3 parameters
 */
struct LTPCommand
{
    enum LTPCommandType cmdType;
    uint16_t param1;
    uint16_t param2;
    uint16_t param3;
};

/**
 * @brief This message is sent by the LTP to the computer. It contains a sample of
 * data with the angle and distance of the LIDAR hit. Angle is 0-4000 and distance is
 * in centinimeres.
 */
struct LTPSample
{
    uint16_t distance;
    uint16_t angle;
};

#endif /* LTP_MESSAGE_H */
