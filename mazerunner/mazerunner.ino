//Mazerunner - a maze solving robot
//Anish Thite, Jordan Schwartz, and Alex Scotte
// the walls are 12 inches long with a 0.5-1 inch gap between them
#include <TECBot_PWMServoDriver.h>
#include <QTRSensors.h>
TECBot_PWMServoDriver drive = TECBot_PWMServoDriver();

#define max_speed 30
//left pins
const int leftPingPin = 10; // Trigger Pin of Ultrasonic Sensor  
const int leftEchoPin = 11; // Echo Pin of Ultrasonic Sensor
//center pins
const int centerPingPin = 8; // Trigger Pin of Ultrasonic Sensor  
const int centerEchoPin = 9; // Echo Pin of Ultrasonic Sensor
//right pins
const int rightPingPin = 12; // Trigger Pin of Ultrasonic Sensor  
const int rightEchoPin = 13; // Echo Pin of Ultrasonic Sensor

//algorithim setup contingency if dynamic doesnt work
#define width 3
#define height 4
#define startuprow 0
#define startupcol 3 

int maze[width][height];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starting Serial Terminal
 //Initialize the PWM controller
  drive.begin();
  drive.setPWMFreq(60);

  delay(1500);
  //Arm the ESC's by sending a "neutral" signal for 1.5 seconds
  drive.setDrive(0,0);
  delay(1500);
}

void loop() {

//go forward until stop
goforward();
// classify junction
//decide and act


//stop all 


Serial.print(getinches(leftPingPin, leftEchoPin));
Serial.print("\t");
Serial.print(getinches(centerPingPin, centerEchoPin));
Serial.print("\t");
Serial.print(getinches(rightPingPin, rightEchoPin));
Serial.println(" ");
delay(100);
}
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

//returns inches from ultrasonic sensors
int getinches(int pingPin,int echoPin) {
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   return cm;
}

void goforward(){
    // go forward if all sensors are activated or path is already explored
  if (getinches(centerPingPin,centerEchoPin) > 3 && getinches(leftPingPin,leftEchoPin)< 6 && getinches(rightPingPin,rightEchoPin) < 6){ 
    //if veering left
    if (getinches(leftPingPin,leftEchoPin) < getinches(rightPingPin,rightEchoPin)){
          drive.setDrive(10,5);  
    }
    //if veering right
    if (getinches(leftPingPin,leftEchoPin) > getinches(rightPingPin,rightEchoPin)){
          drive.setDrive(5,10);
    }
    else{
      drive.setDrive(5,5);
    }
  }
  else{
    drive.setDrive(0,0); 
  }
  //goes forward to center itself in cell

}
//classifies the element and stores it in the array
//classifies: null: not been there yet 0: only one way up 1: dead end 2: 2 way junction 3: 3 way junction 
void classifystore(){}
//void decide(){}
//void turn()}{
void turnLeft90 (){
  float delayy = 335;// a delay of ___ results in 90 degree turn
  drive.setDrive(-30,15);
  delay(delayy);
  drive.setDrive(0,0);
}
void turn180 (){
  float delayy = 573;// a delay of ___ results in 90 degree turn
  drive.setDrive(-30,15);
  delay(delayy);
  drive.setDrive(0,0);
}
void turnRight90 (){
  float delayy = 305;// a delay of ___ results in 90 degree turn
  drive.setDrive(30,-15);
  delay(delayy);
  drive.setDrive(0,0);
}
void PIDUltra() {
  float f,l,r,lastError,i;
  l = getinches(leftPingPin,leftEchoPin);
  r = getinches(rightPingPin, rightEchoPin);
  f = getinches(centerPingPin, centerEchoPin);

  float error = l - r;
  
  float speedDifference = error/5 + i + (error - lastError);
  lastError = error;
  float rightMotor = max_speed + speedDifference;
  float leftMotor = max_speed - speedDifference;
  rightMotor = constrain(rightMotor,0,max_speed);
  leftMotor = constrain(leftMotor,0,max_speed);
  i += error;
  drive.setDrive(leftMotor,rightMotor);
  delay(100);
}

