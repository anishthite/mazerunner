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
//goes forward to center itself in cell
drive.setDrive(5,5);
delay(100);

// classify junction
//decide and act


//stop all 
else{
drive.setDrive(0,0); 
}

Serial.print(getinches(leftPingPin, leftEchoPin));
Serial.print("\t");
Serial.print(getinches(centerPingPin, centerEchoPin));
Serial.print("\t");
Serial.print(getinches(rightPingPin, rightEchoPin));
Serial.println(" ");
delay(100);
}
long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}
//returns inches from ultrasonic sensors
long getinches(int pingPin, int echoPin){
   long duration, inches;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   //Serial.println(duration);
   inches = microsecondsToInches(duration);
   return inches;
  
}
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

