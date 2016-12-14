
#include <PacketSerial.h>
#include "lidar.h"
#include "encoder.h"


LIDAR lidar;
PacketSerial serial;
Encoder encoder;

int motorDuty;
int motorDutyPeriod = 1000; //period in us
unsigned long motorDutyLastTime;
unsigned long motorDutyEndTime =0;
int motorPin = 6;



void setup() {

  //pinMode(motorPin, OUTPUT);
  //digitalWrite(motorPin, LOW);
  
  
  lidar.init();
  
  encoder.init();
  
  // We must specify a packet handler method so that
  serial.setPacketHandler(&onPacket);
  serial.begin(115200);
  
  Serial.println("Booted up!");
  setMotorSpeed(50);

  

}

void loop() {
  // put your main code here, to run repeatedly:
  // serial.update();

  const uint8_t packet1 = lidar.getDistance();
  //serial.send(&packet1, 1);

  
  Serial.print(packet1);
  Serial.print(",");
  Serial.println(encoder.getAngle());

  analogWrite(6, 50);
  //generateMotorSig();
}


void onPacket(const uint8_t* buffer, size_t size)
{
  uint8_t string[17] = "Packet received!";
  
  serial.send(string, 16);
}

void generateMotorSig()
{
  unsigned long curTime = micros();
  if(curTime - motorDutyLastTime > motorDutyEndTime)
  {
    //Serial.println("Toggling! ");
    digitalWrite(motorPin, !digitalRead(motorPin));
    motorDutyLastTime = curTime;
  }
}

void setMotorSpeed(int motorSpeed)
{
  motorDutyEndTime = (double)(motorSpeed)*0.01*motorDutyPeriod;
  Serial.print("MotorDuty end time is: ");
  Serial.println(motorDutyEndTime);
}

