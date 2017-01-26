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
int16_t getAngle(void) {

    int16_t readData;
    uint8_t LSByte;
    uint8_t MSByte;

    SS_ENCODER = 0;
    MSSP1_SPI_Exchange8bit(0x60);
    MSSP1_SPI_Exchange8bit(0x00);
    MSSP1_SPI_Exchange8bit(0x00);
    MSByte = MSSP1_SPI_Exchange8bit(0x00);
    LSByte = MSSP1_SPI_Exchange8bit(0x00);
    SS_ENCODER = 1;
    
    // We shift over the MSB and insert the LSB
    readData = MSByte << 8 | LSByte;
    
    // If we go negative, meaning a counter clockwise cross of the index, do some math and give us the positive number
    if(readData < 0)
        readData = 3999 + readData;
    
    return readData;
}


