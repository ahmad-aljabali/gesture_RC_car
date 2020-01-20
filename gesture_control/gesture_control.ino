#include "MPU9250.h"
#include <SoftwareSerial.h>

//TX_BLUTUTH 10, RX_BLUTUTH 11
SoftwareSerial BTserial(10, 11);
// SDA-A4 & SCL-A5 (IMU-Arduino nano)
MPU9250 IMU(Wire,0x68);

int Xzero, Yzero;
int IMU_status,velocity;

int set_speed(int Xmag){
  int velocity = abs(2*(Xmag-Xzero));
  if(velocity > 255){
    velocity = 255;
  }
}

int set_diriction(int Ymag,int Xmag){
  int dir;
  int code=5000; //stop by default
  if ((Xmag-Xzero)>20 && abs(Ymag-Yzero)<20){
    //forward
    code=1000+velocity;
  }

  if ((Xmag-Xzero)<-20 && abs(Ymag-Yzero)<20){
    //backward
    code=2000+velocity;
  }

  if (Ymag-Yzero>20){
    //left
    code=3000+velocity;
  }

  if (Ymag-Yzero<-20){
    //right
    code=4000+velocity;
  }
  return code;
}

void setup() {
  // serial to display data
  Serial.begin(9600);
  BTserial.begin(38400);

  // start communication with IMU 
  IMU_status = IMU.begin();
  if (IMU_status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.print("Status: ");
    Serial.println(IMU_status);
    while(1) {}
  }
  IMU.readSensor();
  Xzero = int(IMU.getMagX_uT());
  Yzero = int(IMU.getMagY_uT());

}

void loop() {
  // read the sensor
  IMU.readSensor();

  int Xmag = int(IMU.getMagX_uT());
  int Ymag = int(IMU.getMagY_uT());

  velocity = set_speed(Xmag);
  int msg = set_diriction(Xmag,Ymag);

  Serial.println(msg);
  BTserial.write(msg);
  BTserial.write('D');

  Serial.println("ZeroX: ");
  Serial.println(Xzero);
  Serial.print("MagX: ");  
  Serial.print(Xmag,6);
  Serial.println("ZeroY: ");
  Serial.println(Yzero);
  Serial.print("MagY: ");
  Serial.print(Ymag,6);
  
  delay(200);
} 
