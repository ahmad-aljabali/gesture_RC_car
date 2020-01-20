#include <SoftwareSerial.h>

//TX_BLUTUTH 10, RX_BLUTUTH 11
SoftwareSerial BTserial(10, 11); 
int16_t msg;

// motor pins
const int speedFR=A0;
const int dir1FR=3;
const int dir2FR=4;

const int speedFL=A1;
const int dir1FL=5;
const int dir2FL=6;

const int speedBR=A2;
const int dir1BR=7;
const int dir2BR=8;

const int speedBL=A3;
const int dir1BL=12;
const int dir2BL=13;

void set_motor(int velocity){
  //forword
  if (velocity > 1000 && velocity<2000){
    velocity-=1000;
    analogWrite(speedFR, velocity);
    digitalWrite(dir1FR, HIGH);
    digitalWrite(dir2FR, LOW);
    
    analogWrite(speedFL, velocity);
    digitalWrite(dir1FL, HIGH);
    digitalWrite(dir2FL, LOW);
    
    analogWrite(speedBR, velocity);
    digitalWrite(dir1BR, HIGH);
    digitalWrite(dir2BR, LOW);
    
    analogWrite(speedBL, velocity);
    digitalWrite(dir1BL, HIGH);
    digitalWrite(dir2BL, LOW);
    }

  //backword
  if (velocity > 2000 && velocity<3000){
    velocity-=2000;
    analogWrite(speedFR, velocity);
    digitalWrite(dir1FR, LOW);
    digitalWrite(dir2FR, HIGH);
    
    analogWrite(speedFL, velocity);
    digitalWrite(dir1FL, LOW);
    digitalWrite(dir2FL, HIGH);
    
    analogWrite(speedBR, velocity);
    digitalWrite(dir1BR, LOW);
    digitalWrite(dir2BR, HIGH);
    
    analogWrite(speedBL, velocity);
    digitalWrite(dir1BL, LOW);
    digitalWrite(dir2BL, HIGH);
    }

  //left
  if (velocity > 3000 && velocity<4000){
    velocity-=3000;
    analogWrite(speedFR, velocity);
    digitalWrite(dir1FR, HIGH);
    digitalWrite(dir2FR, LOW);
    
    analogWrite(speedFL, velocity);
    digitalWrite(dir1FL, LOW);
    digitalWrite(dir2FL, HIGH);
    
    analogWrite(speedBR, velocity);
    digitalWrite(dir1BR, HIGH);
    digitalWrite(dir2BR, LOW);
    
    analogWrite(speedBL, velocity);
    digitalWrite(dir1BL, LOW);
    digitalWrite(dir2BL, HIGH);
    }

  //right
  if (velocity > 4000 && velocity<5000){
    velocity-=4000;
    analogWrite(speedFR, velocity);
    digitalWrite(dir1FR, LOW);
    digitalWrite(dir2FR, HIGH);
    
    analogWrite(speedFL, velocity);
    digitalWrite(dir1FL, HIGH);
    digitalWrite(dir2FL, LOW);
    
    analogWrite(speedBR, velocity);
    digitalWrite(dir1BR, LOW);
    digitalWrite(dir2BR, HIGH);
    
    analogWrite(speedBL, velocity);
    digitalWrite(dir1BL, HIGH);
    digitalWrite(dir2BL, LOW);
    }

  //STOP!
  if (velocity>=5000){
    velocity=0;
    analogWrite(speedFR, velocity);
    digitalWrite(dir1FR, LOW);
    digitalWrite(dir2FR, LOW);
    
    analogWrite(speedFL, velocity);
    digitalWrite(dir1FL, LOW);
    digitalWrite(dir2FL, LOW);
    
    analogWrite(speedBR, velocity);
    digitalWrite(dir1BR, LOW);
    digitalWrite(dir2BR, LOW);
    
    analogWrite(speedBL, velocity);
    digitalWrite(dir1BL, LOW);
    digitalWrite(dir2BL, LOW);
    }
}


void setup() {
  pinMode(speedFR,OUTPUT);
  pinMode(dir1FR,OUTPUT);
  pinMode(dir2FR,OUTPUT);

  pinMode(speedFL,OUTPUT);
  pinMode(dir1FL,OUTPUT);
  pinMode(dir2FL,OUTPUT);

  pinMode(speedBR,OUTPUT);
  pinMode(dir1BR,OUTPUT);
  pinMode(dir2BR,OUTPUT);

  pinMode(speedBL,OUTPUT);
  pinMode(dir1BL,OUTPUT);
  pinMode(dir2BL,OUTPUT);

  Serial.begin(9600);
  BTserial.begin(38400);

}

void loop() {
  int velocity=0;
  bool recived=false;
  while(recived == false){
    if (BTserial.available()>0) { // Checks whether data is comming from the serial port
      msg = BTserial.read(); // Reads the data from the serial port
      if(msg=='D'){
        recived = true;
      }else{
        velocity = velocity*10;
        velocity = velocity+int(msg);
      }
    }
  }
  set_motor(velocity);

}
