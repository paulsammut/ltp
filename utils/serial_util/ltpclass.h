#ifndef LTPCLASS_H
#define LTPCLASS_H

#include "ltpmessage.h"
#include "serialclass.h"

#ifndef PI
#define PI 3.141592
#endif

/**
 * @brief LTP "hit" containing x,y,z data. This is in the LTP_Body reference frame
 */
typedef struct {
    double hitpos_x;
    double hitpos_y;
    double hitpos_z;
}LtpHitXyz;



/**
 * @brief The LTP Class handles all the function necassary to be able to receive
 * decoded and converted LtpHitXyz data and also send the LTP commands. This class
 * contains a serial port instance so that all the user needs to do is the PollRead()
 * function to get a sample.
 */
class LtpClass
{
private:
    SerialClass ltp_serial_port_;
    uint8_t packet_buffer_[255];
    double head_angel_phi_= (PI/2);;
    
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

    /**
     * @brief Converts an LtpSample that has the raw head angle and distance to
     * LtpHitXyz which are cartesian coordinates in meters.
     *
     * @param ltp_sample pointer to an LtpSample that needs converting
     * @param ltp_hit_xyz pointer to an LtpHitXyz that will fleshed out 
     *
     * @return 1 if success 0 if failed
     */
    int ConvToXyz(const struct LtpSample *ltp_sample, LtpHitXyz *ltp_hit_xyz);

public:
    /**
     * @brief Initializes the LTP by setting up the serial port with the right
     * settings and connecting.
     *
     * @param port_name string containing a valid port name.
     *
     * @return 1 if success, 0 if failed
     */
    uint16_t Init(const char *port_name, double head_phi_radians);

    /**
     * @brief To be called as rapidly as possible. This polls the serial port and
     * returns a message if it finds one.
     *
     * @param ltp_sample pointer to the ltp_sample whose values will be updated
     * with the latest packet.
     *
     * @return 1 if there is a new packet, 0 if not.
     */
    int16_t PollRead(LtpHitXyz *ltp_hit_xyz);

    
    /**
     * @brief Prints an LTP sample to stdout. 
     *
     * @param ltp_sample LTP Sample to print
     */
    void PrintHit(LtpHitXyz *ltp_hit_xyz);

    /**
     * @brief Closes the serial port
     *
     * @return 1 if succesfful, 0 if no
     */
    int16_t Shutdown(void);

    /**
     * @brief Sends a command to the LTP
     *
     * @param input_ltpcommand 
     *
     * @return 1 if success 0 if failed
     */
    int SendCommand(struct LtpCommand *input_ltpcommand);

    /**
     * @brief Sets phi with an argument in radians. See the root README.md for
     * angle reference.
     *
     * @param head_phi_radians double containing phi in radians. 
     */
    void SetHeadPhiRads(double head_phi_radians);

    /**
     * @brief Sets phi with an argument in degrees. See the root README.md for
     * angle reference.
     *
     * @param head_phi_degrees doubel containing phi in degrees
     */
    void SetHeadPhiDegs(double head_phi_degrees);

    
    /**
     * @brief Gets the head phi set in the LtpClass. This value is in radians.
     *
     * @return Head angle phi in radians.
     */
    double GetHeadPhi(void);

};

#endif
