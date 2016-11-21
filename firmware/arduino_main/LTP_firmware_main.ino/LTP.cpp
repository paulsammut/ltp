#include <PacketSerial.h>
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


