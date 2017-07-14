//Mazerunner - a maze solving robot
//Anish Thite, Jordan Schwartz, and Alex Scotte
// the walls are 12 inches long with a 0.5-1 inch gap between them
#include <TECBot_PWMServoDriver.h>
#include <QTRSensors.h>
TECBot_PWMServoDriver drive = TECBot_PWMServoDriver();

int lastError = 0;
#define max_speed 7
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

decide(classifystore());

delay(1000);

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
   //Serial.println("got distance");
   return cm;
}

int classifystore(){  
  int path = 0;
  if (getinches(leftPingPin,leftEchoPin) > 15){
    path +=1;  
  }
  if (getinches(centerPingPin,centerEchoPin) > 15){
    path +=1;
  }
  if (getinches(rightPingPin,rightEchoPin) > 15){
    path +=1;
  }
 
  return path;
}
void decide(int path){
  int r = getinches(rightPingPin, rightEchoPin);
  int l = getinches(leftPingPin, leftEchoPin);
  int f = getinches(centerPingPin, centerEchoPin);
  
  if(path == 1){
    if(r > 15){turnRight90();}
    if(l > 15){turnLeft90();}
    if(f > 15){goforward();}
  }
  else if(path == 2){
    if(r < 15){
      int x = random(2);
      if(x == 0){
        turnLeft90();
      }
      else{
        goforward();
      }
    }
    if(l < 15){
      int x = random(2);
      if(x == 0){
        turnRight90();
      }
      else{
        goforward();
      }
    }
    if(f < 15){
      int x = random(2);
      if(x == 0){
        turnRight90();  
      }
      else{
        turnLeft90();
      }
    }
  }
  else if(path == 3){
    int x = random(3);
    if(x == 0){
      turnLeft90();
    }
    else if(x == 1){
      turnRight90();
    }
    else if(x == 2){
      goforward();
    }
  }
  else if(path == 0){
    turn180();
  }

}
//void turn()}{
void turnLeft90 (){
  float delayy = 335;// a delay of ___ results in 90 degree turn
  drive.setDrive(-30,15);
  delay(delayy);
  drive.setDrive(0,0);

  //Serial.println("turning left");

}
void turn180 (){
  float delayy = 573;// a delay of ___ results in 90 degree turn
  drive.setDrive(-30,15);
  delay(delayy);
  drive.setDrive(0,0);
  goforward();
//Serial.println("turning around");

}
void turnRight90 (){
  float delayy = 305;// a delay of ___ results in 90 degree turn
  drive.setDrive(30,-15);
  delay(delayy);
  drive.setDrive(0,0);
  goforward();

}
void goforward() {
  float f = getinches(centerPingPin, centerEchoPin);
  float endPoint = f-33;

  while(f > endPoint){
    f = getinches(centerPingPin, centerEchoPin);
    goforward2();
  }
  drive.setDrive(0,0);
  
}
void goforward2(){
    // go forward if all sensors are activated or path is already explored
//  if (getinches(centerPingPin,centerEchoPin) > 7 && getinches(leftPingPin,leftEchoPin)< 15 && getinches(rightPingPin,rightEchoPin) < 15){ 
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
