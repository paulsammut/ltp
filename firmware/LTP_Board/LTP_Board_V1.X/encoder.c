#include "encoder.h"
#include "mcc_generated_files/mcc.h"
#include "LTP_system.h"
void encoder_init(void) {

    /*
      SPI.begin();
      pinMode(m_ssPin, OUTPUT);
      digitalWrite(m_ssPin, HIGH); //idle high
      // Initialize the LS3663
      digitalWrite(m_ssPin, LOW);
      SPI.transfer(0x88);   // Write to MRD0
      SPI.transfer(0x23);   // x4 quadrature, Index resets CNTR
      digitalWrite(m_ssPin, HIGH);
     * 
     */
    
    SS_ENCODER = 0;

    MSSP1_SPI_Exchange8bit(0x88);// Write to MRD0
    MSSP1_SPI_Exchange8bit(0x23);// x4 quadrature, Index resets CNTR
    SS_ENCODER = 1;    

}

/*  This function does an SPI read of the CNTR register which is a 4 byte register. 
 *  In it, is the current angle of the LIDAR head. 
 */
uint16_t getAngle(void) {
    /*

  unsigned char byteMSB, byteLSB;
  digitalWrite(m_ssPin, LOW);
  SPI.transfer(0x60);   // Read CNTR
  SPI.transfer(0x00);   
  SPI.transfer(0x00);
  byteMSB = SPI.transfer(0x00);
  byteLSB = SPI.transfer(0x00);
  digitalWrite(m_ssPin, HIGH);

  //Debug block
  //Serial.print("ByteMSB: ");
  //Serial.print(byteMSB, HEX);
  //Serial.print(" ByteLSB: ");
  //Serial.println(byteLSB, HEX);
         
  
  m_curAngle = byteMSB << 8 | byteLSB;
  return m_curAngle;
     */

    uint16_t readData;
    uint8_t LSByte;
    uint8_t MSByte;
    
    //read MRD1
    SS_ENCODER = 0;

    MSSP1_SPI_Exchange8bit(0x48);
    LSByte = MSSP1_SPI_Exchange8bit(0x00);
    SS_ENCODER = 1;
    
    /*
    SS_ENCODER = 0;
    MSSP1_SPI_Exchange8bit(0x60);
    MSSP1_SPI_Exchange8bit(0x00);
    MSSP1_SPI_Exchange8bit(0x00);
    MSByte = MSSP1_SPI_Exchange8bit(0x00);
    LSByte = MSSP1_SPI_Exchange8bit(0x00);
    readData = MSByte << 8 || LSByte;
    SS_ENCODER = 1;
    */
    
    return LSByte;
}


