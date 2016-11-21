#ifndef LTP_H
#define LTP_H

class LTP
{
  private:
    int m_sampleRate;
    int m_actualRMP;
    int m_motorPower;
    int m_curMeasurement;
    int m_curAngle;
    bool m_debug;
    bool m_run;
  public:
    LTP();
    void setSample(int angle, int measurement);
    void setAngle(int angle);
    void setMeasurement(int measurement);
};

#endif
