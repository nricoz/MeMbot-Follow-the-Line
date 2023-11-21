#include <Arduino.h>
#include <MeMCore.h>
#include <stdlib.h>
#include <time.h>

MeLineFollower lineFinder(PORT_3);

MeDCMotor motor1(M1); // Right 
MeDCMotor motor2(M2); // Left

double counter = 0;

void detectLines();
void moveRobot(int leftMotor, int rightMotor, int delayTime);

int randomNumber(){
    int finalnum = 0;
    int randomNumber = 1+(rand()%2);

    if (randomNumber == 1){
      finalnum = -160;
    } else {
      finalnum = -140;
    }

    return finalnum;
  }


void setup() {
  srand(time(NULL));
  //put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  //put your main code here, to run repeatedly:
  if(counter < 360){
    detectLines();
  }
}

void detectLines(){
    if(lineFinder.readSensor1()==0 && lineFinder.readSensor2()==0){
      Serial.println("Sensor 1 on black and Sensor2 on black");
      moveRobot(-150, 150, 50);
      counter--;
    } else if(lineFinder.readSensor1()==1 && lineFinder.readSensor2()==0){
      Serial.println("Sensor 1 on white and Sensor 2 on black");
      moveRobot(-200, -100, 50);
      counter+=0.125;
    } else if(lineFinder.readSensor1() == 0 && lineFinder.readSensor2()==1){
      Serial.println("Sensor 1 on Black and Sensor 2 on White");
      moveRobot(100, 200, 50);
      counter+=0.125;
    } else {
      Serial.println("Sensor 1 on White and Sensor 2 on White");
      moveRobot(150, randomNumber(), 80);
      counter+=2;
    }
  
  delay(20);
}

void moveRobot(int leftMotor, int rightMotor, int delayTime){
  motor2.run(leftMotor);
  motor1.run(rightMotor);
  delay(delayTime);
  motor1.stop();
  motor2.stop();
} 
