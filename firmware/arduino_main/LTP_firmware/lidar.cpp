// This file
#include "lidar.h"

/*
   LIDAR()

   Default constructor where we initialize some variables

*/
LIDAR::LIDAR()
{

}

void LIDAR::init()
{
  m_curDistance = 0;
  m_biasCounter = 0;  // this is used to do a bias correction
  m_biasTreshold = 100; // the datasheet says to do this every 100 samples

  m_LIDAR.begin(0, true); // Set configuration to default and I2C to 400 kHz
  m_LIDAR.configure(1); // Change this number to try out alternate configurations
}


/*
   getSample()

   Gets a sample from the LTP and does bias correction whenever a bias treshold is reached

*/
int LIDAR::getDistance()
{
  m_biasCounter++;

  if (m_biasCounter >= m_biasTreshold)
  {
    m_curDistance = m_LIDAR.distance();
    m_biasCounter = 0;
  }
  else
  {
    m_curDistance = m_LIDAR.distance(false);
  }

  return m_curDistance;
}
