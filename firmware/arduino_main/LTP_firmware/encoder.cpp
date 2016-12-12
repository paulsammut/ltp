#include "encoder.h"

Encoder::Encoder()
{

}


Encoder::init()
{
  SPI.begin();
  pinMode(m_ssPin, OUTPUT);
  digitalWrite(m_ssPin, HIGH); //idle high

  // Initialize the LS3663
  digitalWrite(m_ssPin, LOW);
  SPI.transfer(0x88);   // Write to MRD0
  SPI.transfer(0x23);   // x4 quadrature, Index resets CNTR
  digitalWrite(m_ssPin, HIGH);
}

/*  This function does an SPI read of the CNTR register which is a 4 byte register. 
 *  In it, is the current angle of the LIDAR head. 
 */
unsigned int Encoder::getAngle()
{
  unsigned char byteMSB, byteLSB;
  digitalWrite(m_ssPin, LOW);
  SPI.transfer(0x60);   // Read CNTR
  SPI.transfer(0x00);   
  SPI.transfer(0x00);
  byteMSB = SPI.transfer(0x00);
  byteLSB = SPI.transfer(0x00);
  digitalWrite(m_ssPin, HIGH);

  /* Debug block
  Serial.print("ByteMSB: ");
  Serial.print(byteMSB, HEX);
  Serial.print(" ByteLSB: ");
  Serial.println(byteLSB, HEX);
  */
  m_curAngle = byteMSB << 8 | byteLSB;
  return m_curAngle;
}

