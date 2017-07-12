//Mazerunner - a maze solving robot
//Anish Thite, Jordan Schwartz, and Alex Scotte

#include <TECBot_PWMServoDriver.h>
TECBot_PWMServoDriver drive = TECBot_PWMServoDriver();

//left pins
const int leftPingPin = 10; // Trigger Pin of Ultrasonic Sensor  
const int leftEchoPin = 11; // Echo Pin of Ultrasonic Sensor
//right pins
const int centerPingPin = 8; // Trigger Pin of Ultrasonic Sensor  
const int centerEchoPin = 9; // Echo Pin of Ultrasonic Sensor
//center pins
const int rightPingPin = 13; // Trigger Pin of Ultrasonic Sensor  
const int rightEchoPin = 12; // Echo Pin of Ultrasonic Sensor

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
