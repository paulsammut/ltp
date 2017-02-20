#include "mcc_generated_files/uart1.h"
#include "serialComms.h"
#include "cobs.h"

//#define _DEBUG
#include "dbg.h"

uint8_t buff_RxUnstuffed[255];
uint8_t buff_RxStuffed[255];
uint8_t buff_TxStuffed[255];
size_t tempLength;
size_t TxPacketLength;

int sendLTPSample(struct LtpSample *sendSample) {
    // convert the LTPSample to a byte array
    uint8_t *sampleBytes = (uint8_t*) sendSample;

    // this byte array is our "input" array. Get the length of it
    TxPacketLength = sizeof (struct LtpSample);

    // Make sure our tx packet is not too long. This should never happen
    if (TxPacketLength >= 251)
        return 0;

    // encode the "input" array with COBS. Encode it to our buffer array, buff_TxStuffed
    tempLength = cobs_encode(sampleBytes, TxPacketLength, buff_TxStuffed);

    // Make sure our encoded COBS packet is not too long. If it is longer than 255 that it 
    // won't be able to be decoded
    if (tempLength >= 253)
        return 0;

    int i;
    for (i = 0; i < tempLength; i++) {
        // write the current byte.
        UART1_Write(buff_TxStuffed[i]);

        // Wait for the transmission to complete
        while (!(UART1_StatusGet() & UART1_TX_COMPLETE)) {
        }
    }

    // Terminate our COBS packet with a 0x00
    UART1_Write(0x00);
    while (!(UART1_StatusGet() & UART1_TX_COMPLETE)) {
    }
    
    return 1;
}

void cobsTest(struct LtpSample *sendSample) {
    uint8_t *sampleBytes = (uint8_t*) sendSample;
    TxPacketLength = sizeof (struct LtpSample);

    tempLength = cobs_encode(sampleBytes, TxPacketLength, buff_TxStuffed);


    dbg_printf("\r\nRaw: ");
    int i = 0;
    for (i = 0; i < TxPacketLength; i++) {
        dbg_printf(" 0x%02x ", sampleBytes[i]);
    }
    dbg_printf("\r\nEnc: ");
    for (i = 0; i < tempLength; i++) {
        dbg_printf(" 0x%02x ", buff_TxStuffed[i]);
    }

    tempLength = cobs_decode(buff_TxStuffed, tempLength, buff_RxUnstuffed);
    dbg_printf("\r\nUns: ");
    for (i = 0; i < tempLength; i++) {
        dbg_printf(" 0x%02x ", buff_RxUnstuffed[i]);
    }
    //UART1_Write( *(sampleBytes + i));

    while (!(UART1_StatusGet() & UART1_TX_COMPLETE)) {
        // Wait for the tranmission to complete
    }
}