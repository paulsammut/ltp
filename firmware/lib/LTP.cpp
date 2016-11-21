// LTP class file
// LTP stands for Lidar Test Platfrom 
// By Paul Sammut , Nov 2016

class LTP
{
private:
    int m_samplerate;
    int m_actualRMP;
    int m_motorpower;
    int m_curMeasurement;
    int m_curAngle;
    bool m_debug;
    bool m_run;

public:
    void setSample(int angle, int measurement)
    {
        m_curAngle = angle;
        m_curMeasurement = measurement;
    }

    void setAngle(int angle)
        m_curAngle = angle;

    void setMeasurement(int measurement)
        m_curMeasurement = measurement;
};

