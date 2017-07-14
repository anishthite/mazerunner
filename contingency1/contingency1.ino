#include <TECBot_PWMServoDriver.h>
TECBot_PWMServoDriver drive = TECBot_PWMServoDriver();


void setup() {  
  // put your setup code here, to run once:
 Serial.begin(9600);

    //Initialize the PWM Driver board
    drive.begin();
    drive.setPWMFreq(60);

    //Arm the ESC's
    drive.setDrive(0,0);
    delay(1500);
}

void loop() {
  // put your main code here, to run repeatedly:

}
