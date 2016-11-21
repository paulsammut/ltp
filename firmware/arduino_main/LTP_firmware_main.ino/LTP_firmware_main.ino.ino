#include <PacketSerial.h>

#include "LTP.h"

LTP ltp;

void setup() {
  // put your setup code here, to run once:
  
  ltp.init();

}

void loop() {
  // put your main code here, to run repeatedly:
  ltp.loopCycle();
}
