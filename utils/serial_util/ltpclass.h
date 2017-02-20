#ifndef LTPCLASS_H
#define LTPCLASS_H

#include "LTP_message.h"
#include "serial.h"

class LtpClass
{
private:
    SerialClass m_ltp_serial_port;

public:
    /**
     * @brief Initializes the LTP by setting up the serial port with the right
     * settings and connecting.
     *
     * @param port_name string containing a valid port name.
     */
    void InitLtp(const uint8_t *port_name);

    /**
     * @brief To be called as rapidly as possible. This polls the serial port and
     * returns a message if it finds one.
     *
     * @param ltp_sample pointer to the ltp_sample whose values will be updated
     * with the latest packet.
     *
     * @return 1 if there is a new packet, 0 if not.
     */
    int16_t PollReadLtp(const struct LTPSample *ltp_sample);

    
    /**
     * @brief Prints an LTP sample to stdout. 
     *
     * @param ltp_sample LTP Sample to print
     */
    void PrintLtpSample(const struct LTPSample *ltp_sample);
};

#endif
