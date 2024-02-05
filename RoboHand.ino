//Robo Hand By 


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver driverBoard = Adafruit_PWMServoDriver();

#define SERVOMIN 160
#define SERVOMAX 520

#define SERVO1 7 // position 7 on the servo board
#define SERVO2 8 // position 8 on the servo board
#define SERVO3 5 // position 5 on the servo board

int SensorIn = A0;
int ButtonIn = 2;
int threshold = 512;
//State control 0=Ready, 1=Moving Down, 2=Moving UP
int state =0;
int servoPos = 90;


void setup() {
  // put your setup code here, to run once:
  driverBoard.begin();
  driverBoard.setPWMFreq(60);
  //Setup Button and Sensor Bin as input
  pinMode(ButtonIn,INPUT);
  delay(10);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int pulse = 0;
  int sensorRead = analogRead(SensorIn);
  int buttonState = digitalRead(ButtonIn);
  Serial.println(sensorRead);
  if(state==1 && buttonState == 1)
  {
    state=2;
  }
  if(state==0 && sensorRead > threshold)
  {
    state = 1;
  }
  if(state == 2 and servoPos <=90)
  {
    state =0;
  }
  if(state==1)
  {
    servoPos++;
    servoDegree(SERVO1, servoPos);
  }
  if(state==2)
  {
    servoPos--;
    servoDegree(SERVO1, servoPos);
  }
/*
  for(int pos=0; pos <= 179; pos +=1) {
    servoDegree(SERVO1, pos);
    servoDegree(SERVO2, pos);
    servoDegree(SERVO3, pos);
    delay(15);
  }
  for(int pos = SERVOMAX; pos >= SERVOMIN; pos -= 1) {
    driverBoard.setPWM(SERVO1, 0, pos);
    driverBoard.setPWM(SERVO2, 0, pos);
    driverBoard.setPWM(SERVO3, 0, pos);
    delay(15);
  }*/
}

void servoDegree(int servoNum, int degree) {
  driverBoard.setPWM(servoNum, 0, map(degree, 0, 179, SERVOMIN, SERVOMAX));
}