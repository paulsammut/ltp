
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
  //setPwmFrequency(6, 256);

  

}

void loop() {
  // put your main code here, to run repeatedly:
  // serial.update();

  const uint8_t packet1 = lidar.getDistance();
  //serial.send(&packet1, 1);

  
  Serial.print(packet1);
  Serial.print(",");
  Serial.println(encoder.getAngle());

  //analogWrite(6, 50);
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

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

