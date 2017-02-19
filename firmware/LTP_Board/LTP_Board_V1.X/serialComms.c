#include "mcc_generated_files/uart1.h"
#include "serialComms.h"
#include "cobs.h"

uint8_t buff_RxStuffed[255];
uint8_t buff_TxStuffed[255];
size_t tempLength;
size_t TxPacketLength;

void sendLTPSample(struct LTPSample *sendSample) {
    uint8_t *sampleBytes = (uint8_t*) sendSample;
    TxPacketLength = sizeof(struct LTPSample);
    
    tempLength = cobs_encode(sampleBytes, TxPacketLength, buff_TxStuffed);
    
    
    int i = 0;
    for (i = 0; i < TxPacketLength; i++)
        UART1_Write( *(sampleBytes + i));
  
    while (!(UART1_StatusGet() & UART1_TX_COMPLETE)) {
        // Wait for the tranmission to complete
    }
}