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

  turn(90);
}

void loop() {

}

void turn (int i){
  float delayy = i*7.22;// a delay of ___ results in 90 degree turn
  drive.setDrive(-15,7.5);
  delay(delayy);
  drive.setDrive(0,0);
}

