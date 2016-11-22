#ifndef LTP_H
#define LTP_H

#include <LIDARLite.h>
#include <PacketSerial.h>


void setSample(int angle, int measurement);
void setAngle(int angle);
void setMeasurement(int measurement);
void initLTP();
void getSample();

// This is the callback function for the packet received system.
void getPacket(const uint8_t* buffer, size_t size);

// This runs the necassary the code to update every cycle. Relies of millis()
void loopCycle();

#endif
