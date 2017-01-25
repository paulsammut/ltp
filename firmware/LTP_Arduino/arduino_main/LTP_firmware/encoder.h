#include <SPI.h>


class Encoder
{
private:
  const int m_ssPin=10;
  int m_curAngle=0;
  
public:
  Encoder();
  init();
  unsigned int getAngle();
};

