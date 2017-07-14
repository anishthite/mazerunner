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
bool r;
bool l;
bool f;
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
delay(10);

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
    bool l = false;
  }
  else{bool l = true;}
  delay(10);
  if (getinches(centerPingPin,centerEchoPin) > 15){
    path +=1;
    bool f = false;
  }
  else{bool f = true;}
  delay(10);
  if (getinches(rightPingPin,rightEchoPin) > 15){
    path +=1;
    bool r = false;
  }
  else{bool r = true;}
  delay(10);

  return path;
}
void decide(int path){
  int r = getinches(rightPingPin, rightEchoPin);
  delay(10);
  int l = getinches(leftPingPin, leftEchoPin);
  delay(10);
  int f = getinches(centerPingPin, centerEchoPin);
  delay(10);
  if(path == 1){
    if(r > 15){turnRight90();}
    else if(l > 15){turnLeft90();}
    else if(f > 15){goforward();}
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
  float delayy = 305;// a delay of ___ results in 90 degree turn
  drive.setDrive(-30,15);
  delay(delayy);
  drive.setDrive(0,0);
  goforward();

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
//  float f = getinches(centerPingPin, centerEchoPin);
//  delay(100);
//  float r = getinches(rightPingPin, rightEchoPin);
//  delay(100);
//  float l = getinches(leftPingPin, leftEchoPin);
//  delay(100);
//  
//  float endPoint = f-33;

  do{
  if (getinches(leftPingPin,leftEchoPin) > 15){
    bool l = false;
  }
  else{bool l = true;}
  delay(10);
  if (getinches(centerPingPin,centerEchoPin) > 15){
    bool f = false;
  }
  else{bool f = true;}
  delay(10);
  if (getinches(rightPingPin,rightEchoPin) > 15){
    bool r = false;
  }
  else{bool r = true;}
  
  delay(10);
  Serial.println("about to go forward");
  goforward2();
  
  delay(10);
  }while(r == true && l == true && f == false);
  drive.setDrive(0,0);
  
}
void goforward2(){
  float f = getinches(centerPingPin, centerEchoPin);
  delay(10);
  float r = getinches(rightPingPin, rightEchoPin);
  delay(10);
  float l = getinches(leftPingPin, leftEchoPin);
  delay(10);
    if (l < r){
          drive.setDrive(10,5);  
    }
    delay(10);
    //if veering right
    if (l > r){
          drive.setDrive(5,10);
    }
    else{
      drive.setDrive(5,5);
    }
 


}
