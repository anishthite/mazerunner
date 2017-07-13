#include <TECBot_PWMServoDriver.h>

TECBot_PWMServoDriver drive = TECBot_PWMServoDriver();


void setup() {
  Serial.begin(9600);

  //Initialize the PWM controller
  drive.begin();
  drive.setPWMFreq(60);

  //Arm the ESC's by sending a "neutral" signal for 1.5 seconds
  drive.setDrive(0,0);
  delay(1500);

}

void loop() {

}

void turn90 (){
  float delayy = 165;// a delay of ___ results in 90 degree turn
  drive.setDrive(-100,100);
  delay(delayy);
  drive.setDrive(0,0);
}
void turn180 (){
  float delayy = 313;// a delay of ___ results in 90 degree turn
  drive.setDrive(-100,100);
  delay(delayy);
  drive.setDrive(0,0);
}


