//Mazerunner - a maze solving robot
//Anish Thite, Jordan Schwartz, and Alex Scotte

#include <TECBot_PWMServoDriver.h>
TECBot_PWMServoDriver drive = TECBot_PWMServoDriver();

//left pins
const int leftpingPin = 10; // Trigger Pin of Ultrasonic Sensor  
const int leftechoPin = 11; // Echo Pin of Ultrasonic Sensor
//right pins
const int centerpingPin = 8; // Trigger Pin of Ultrasonic Sensor  
const int centerechoPin = 9; // Echo Pin of Ultrasonic Sensor
//center pins
const int rightpingPin = 13; // Trigger Pin of Ultrasonic Sensor  
const int rightechoPin = 12; // Echo Pin of Ultrasonic Sensor

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
