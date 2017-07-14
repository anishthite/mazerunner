///Mazerunner - a maze solving robot
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
int x = 0;
int y = 0;
//go forward until stop
goforward();


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
void decide(int x, int y){
  if (getinches(centerPingPin, centerEchoPin)< 8 && getinches(leftPingPin, leftEchoPin) <= 16 && getinches(rightPingPin, rightEchoPin)>= 20) {
      turnRight90 ();
      
  }
  if (getinches(centerPingPin, centerEchoPin)< 8 && getinches(leftPingPin, leftEchoPin) >= 20 && getinches(rightPingPin, rightEchoPin)> 16) {
      turnLeft90 ();
  
  } 
   if (getinches(centerPingPin, centerEchoPin)< 8 && getinches(leftPingPin, leftEchoPin) <= 20 && getinches(rightPingPin, rightEchoPin)<= 20) {
      turn180 ();
      }
   if (getinches(centerPingPin, centerEchoPin) >=20 && getinches(leftPingPin, leftEchoPin) >= 20 && getinches(rightPingPin, rightEchoPin)>= 20) {
      turnRight90 ();
      
  }

}
