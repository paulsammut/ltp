#ifndef LTP_H
#define LTP_H

#include <LIDARLite.h>
#include <PacketSerial.h>


class LTP
{
  private:
    PacketSerial m_serial;
    LIDARLite m_LIDAR;
    int m_sampleRate;
    int m_actualRMP;
    int m_motorPower;
    int m_curMeasurement;
    int m_curAngle;
    int m_biasCounter;
    int m_biasTreshold;
    bool m_debug;
    bool m_run;
  public:
    LTP();
    void setSample(int angle, int measurement);
    void setAngle(int angle);
    void setMeasurement(int measurement);
    void init();
    void getSample();
    
    // This is the callback function for the packet received system. 
    static void getPacket(const uint8_t* buffer, size_t size);

    // This runs the necassary the code to update every cycle. Relies of millis()
    void loopCycle();
    
};

#endif
