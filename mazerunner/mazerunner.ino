//Mazerunner - a maze solving robot
//Anish Thite, Jordan Schwartz, and Alex Scotte
// the walls are 12 inches long with a 0.5-1 inch gap between them
#include <TECBot_PWMServoDriver.h>
#include <QTRSensors.h>
TECBot_PWMServoDriver drive = TECBot_PWMServoDriver();

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

//algorithim setup contingency if dynamic doesnt work
#define width 3
#define height 4
int posrow  = 0;
int poscol =  3; 

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
//instantiate array
  for (int i = 0; i < width; i++){
   for (int j = 0; j < height; j++){
      maze[i][j] = 0;
    }  
  }
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
  /*if (getinches(centerPingPin,centerEchoPin) > 7 && getinches(leftPingPin,leftEchoPin)< 15 && getinches(rightPingPin,rightEchoPin) < 15){ 
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
  }*/
while (getinches(centerPingPin,centerEchoPin) > 7 && getinches(leftPingPin,leftEchoPin) < 15 && getinches(rightPingPin,rightEchoPin) < 15){
  float f,l,r,lastError,i;
  l = getinches(leftPingPin,leftEchoPin);
  r = getinches(rightPingPin, rightEchoPin);
  f = getinches(centerPingPin, centerEchoPin);

  float error = l - r;
  
  float speedDifference = error/3; //+ i + (error - lastError);
  lastError = error;
  float rightMotor = max_speed + speedDifference;
  float leftMotor = max_speed - speedDifference;
  rightMotor = constrain(rightMotor,0,max_speed);
  leftMotor = constrain(leftMotor,0,max_speed);
  i += error;
  drive.setDrive(leftMotor,rightMotor);
  delay(100);
  //goes forward to center itself in cell
}
drive.setDrive(0,0);
}
//classifies the element and stores it in the array
//classifies: 0: not been there yet 1: only one way up  2: 2 way junction 3: 3 way junction 4: dead end 
void classifystore(){  
  int path = 0;
  if (getinches(leftPingPin,leftEchoPin) > 6){
    path +=1;  
  }
  if (getinches(centerPingPin,centerEchoPin) > 6){
    path +=1;
  }
  if (getinches(rightPingPin,rightEchoPin) > 6){
    path +=1;
  }
  //classify 1
  if (path == 1){
    maze[posrow][poscol] = 1;       
  }
  //classify 2
  if (path == 2){
    maze[posrow][poscol] = 2;
  }
  //classify 3
  if (path == 3){
    maze[posrow][poscol] = 3;
  }
  //classify 4  
  if (path == 0){
    maze[posrow][poscol] = 4;
    path = 4;
  }
  return path;
}
void decide(){ //potentially can input path
  if (getinches(centerPingPin, centerEchoPin)< 3 && getinches(leftPingPin, leftEchoPin) <= 6 && getinches(rightPingPin, rightEchoPin)>= 8) {
      turnRight90 ();
  }
  if (getinches(centerPingPin, centerEchoPin)< 3 && getinches(leftPingPin, leftEchoPin) >= 8 && getinches(rightPingPin, rightEchoPin)> 6) {
      turnLeft90 ();
  
  } 
   if (getinches(centerPingPin, centerEchoPin)< 3 && getinches(leftPingPin, leftEchoPin) <= 8 && getinches(rightPingPin, rightEchoPin)<= 8) {
      turn180 ();
   }
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

