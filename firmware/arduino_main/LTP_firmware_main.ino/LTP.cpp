#include "LTP.h"

// LTP class file
// LTP stands for Lidar Test Platfrom
// By Paul Sammut , Nov 2016


LTP::LTP()
{
  m_sampleRate = 100;
  m_actualRMP = 0;
  m_motorPower = 0;
  m_curMeasurement = 0;
  m_curAngle = 0;
  m_debug = false;
  m_run = false;
  m_biasCounter = 0; // this is used to do a bias correction
  m_biasTreshold = 100; // the datasheet says to do this every 100 samples
}

void LTP::setSample(int angle, int measurement)
{
  m_curAngle = angle;
  m_curMeasurement = measurement;
}

void LTP::setAngle(int angle)
{
  m_curAngle = angle;
}

void LTP::setMeasurement(int measurement)
{
  m_curMeasurement = measurement;
}

void LTP::init()
{
  m_LIDAR.begin(0, true); // Set configuration to default and I2C to 400 kHz
  m_LIDAR.configure(0); // Change this number to try out alternate configurations

  // We must specify a packet handler method so that
  m_serial.setPacketHandler(&LTP::getPacket);
  m_serial.begin(115200);

  Serial.println("Initialized LTP");

}

/*
 * getSample()
 * 
 * Gets a sample from the LTP and does bias correction whenever a bias treshold is reached
 * 
 */
void LTP::getSample()
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

void LTP::getPacket(const uint8_t* buffer, size_t size)
{
  Serial.println("Get packet invoked! Yay!");
}

void LTP::loopCycle()
{
  LTP::getSample();
  //Serial.println(this->m_curMeasurement);
  //Serial.println("looping");
  m_serial.update();
}





