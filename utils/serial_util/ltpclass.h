#ifndef LTPCLASS_H
#define LTPCLASS_H

#include "ltpmessage.h"
#include "serialclass.h"

class LtpClass
{
private:
    SerialClass ltp_serial_port_;
    uint8_t packet_buffer_[255];

    
    /**
     * @brief Decodes a raw COBS packet into an LTP sample.
     *
     * @param rawPacket
     * @param rawPacketLength
     * @param sample1
     *
     * @return 
     */
    uint16_t DecodePacket(
            const uint8_t *raw_packet, 
            size_t raw_packet_length, 
            struct LtpSample *sample1);

public:
    /**
     * @brief Initializes the LTP by setting up the serial port with the right
     * settings and connecting.
     *
     * @param port_name string containing a valid port name.
     *
     * @return 1 if success, 0 if failed
     */
    uint16_t InitLtp(const char *port_name);

    /**
     * @brief To be called as rapidly as possible. This polls the serial port and
     * returns a message if it finds one.
     *
     * @param ltp_sample pointer to the ltp_sample whose values will be updated
     * with the latest packet.
     *
     * @return 1 if there is a new packet, 0 if not.
     */
    int16_t PollReadLtp(struct LtpSample *ltp_sample);

    
    /**
     * @brief Prints an LTP sample to stdout. 
     *
     * @param ltp_sample LTP Sample to print
     */
    void PrintLtpSample(const struct LtpSample *ltp_sample);

    /**
     * @brief Closes the serial port
     *
     * @return 1 if succesfful, 0 if no
     */
    int16_t Shutdown(void);

    int SendCommand(struct LtpCommand *input_ltpcommand);
};

#endif
