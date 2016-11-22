#include "LTP.h"

// LTP file
// LTP stands for Lidar Test Platfrom
// By Paul Sammut , Nov 2016

PacketSerial m_serial;
LIDARLite m_LIDAR;
int m_sampleRate  = 100;;
int m_actualRMP;
int m_motorPower;
int m_curMeasurement;
int m_curAngle;
int m_biasCounter = 0;  // this is used to do a bias correction
int m_biasTreshold = 100; // the datasheet says to do this every 100 samples
bool m_debug = false;
bool m_run = false;


void setSample(int angle, int measurement)
{
  m_curAngle = angle;
  m_curMeasurement = measurement;
}

void setAngle(int angle)
{
  m_curAngle = angle;
}

void setMeasurement(int measurement)
{
  m_curMeasurement = measurement;
}

void initLTP()
{
  m_LIDAR.begin(0, true); // Set configuration to default and I2C to 400 kHz
  m_LIDAR.configure(0); // Change this number to try out alternate configurations

  // We must specify a packet handler method so that
  m_serial.setPacketHandler(&getPacket);
  m_serial.begin(115200);

  Serial.println("Initialized LTP");

}

/*
 * getSample()
 * 
 * Gets a sample from the LTP and does bias correction whenever a bias treshold is reached
 * 
 */
void getSample()
{
  m_biasCounter++;
  
  if (m_biasCounter >= m_biasTreshold)
  {
    m_curMeasurement = m_LIDAR.distance();
    m_biasCounter = 0;
    return;
  }
  else
  {
    m_curMeasurement = m_LIDAR.distance(false);
  }
}

void getPacket(const uint8_t* buffer, size_t size)
{
  Serial.println("Get packet invoked! Yay!");
}

void loopCycle()
{
  getSample();
  //Serial.println(this->m_curMeasurement);
  //Serial.println("looping");
  m_serial.update();
}





