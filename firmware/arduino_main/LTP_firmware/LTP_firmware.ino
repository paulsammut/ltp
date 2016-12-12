
#include <PacketSerial.h>
#include "lidar.h"
#include "encoder.h"


LIDAR lidar;
PacketSerial serial;
Encoder encoder;

void setup() {
  
  lidar.init();
  encoder.init();
  // We must specify a packet handler method so that
  serial.setPacketHandler(&onPacket);
  serial.begin(115200);
  
  Serial.println("Booted up!");

  

}

void loop() {
  // put your main code here, to run repeatedly:
  // serial.update();

  const uint8_t packet1 = lidar.getDistance();
  //serial.send(&packet1, 1);

  delay(10);
  Serial.print(packet1);
  Serial.print(" ");
  Serial.println(encoder.getAngle());
  
}


void onPacket(const uint8_t* buffer, size_t size)
{
  uint8_t string[17] = "Packet received!";
  
  serial.send(string, 16);
}

