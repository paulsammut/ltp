#pragma once

#include <LIDARLite.h>
#include <Wire.h>

class LIDAR
{
private:
    LIDARLite m_LIDAR;
    int m_curDistance;
    int m_biasCounter;  // this is used to do a bias correction
    int m_biasTreshold; // the datasheet says to do this every 100 samples

public:
    LIDAR();
    void init();

    int getDistance();
};
