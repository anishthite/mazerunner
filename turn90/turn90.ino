#include <TECBot_PWMServoDriver.h>
#include <FaBo9Axis_MPU9250.h>


//speed will never exceed this value
#define max_speed 15
double theta;
double theta2;

//initialize mpu and drive objects
FaBo9Axis mpu;
TECBot_PWMServoDriver drive = TECBot_PWMServoDriver();

void setup() {
  Serial.begin(9600);

  //Initialize the PWM controller
  drive.begin();
  drive.setPWMFreq(60);

  //Arm the ESC's by sending a "neutral" signal for 1.5 seconds
  drive.setDrive(0,0);
  delay(1500);

  drive.setDrive(-15,-15);
  delay(1000);
  drive.setDrive(0,0);
  delay(500);

  
  float mx,my,mz;
  mpu.begin();
  delay(100);
  mpu.readMagnetXYZ(&mx,&my,&mz);
  theta = atan2((my - 33),(mx + 77));
  theta = theta*(180/PI);
  if(theta < 0) {
    theta = -theta;
    float x = 180-theta;
    theta = 180 + x;

}
}
void loop() {  
  float startingPoint = theta;
  float goal = theta + 90;
  if (goal > 360){
    goal -= 360;
  }
  Serial.println(goal);

  while(theta2 < goal-5) {
    float mx,my,mz;
    delay(10);
    mpu.readMagnetXYZ(&mx,&my,&mz);
    theta2 = atan2((my - 33),(mx + 77));
    theta2 = theta2*(180/PI);
    if(theta2 < 0) {
      theta2 = -theta2;
      float x = 180-theta2;
      theta2 = 180 + x;
  }   
  
      Serial.print(goal);
      Serial.print("    ");
      Serial.println(theta2);

    
    drive.setDrive(-15,15);
  }
  drive.setDrive(0,0);
  
}






