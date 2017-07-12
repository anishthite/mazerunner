/*
 * Simple Drive test
 * By: Greg Armstrong
 * June 2017
 * 
 * This program makes use of the TEC Bot drive functions to test the drive motors and a servo.
 * 
 * available functions
 * 
 * setDrive(leftPower, rightPower)
 * Sets the speed of both drive motors at once. Assumes the motors are connected to ports 0 and 1
 * on the PWM driver board. leftPower and rightPower are numbers between -100 and 100
 * 
 * setMotor(num, power)
 * Sets a single motor (attached to port "num") to a speed.
 * power is an integer between -100 and 100
 * 
 * setServo(num, position)
 * Sets a servo attached to port "num" to an angle defined by position.
 * position is an integer between 0 and 180
 */

#include <TECBot_PWMServoDriver.h>
#include <FaBo9Axis_MPU9250.h>

//middle is the desired setpoint. Last error is the previous error (used for derivative calculation)
float middle;
float lastError = 0;
float i = 0;

//speed will never exceed this value
#define max_speed 15

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

  // starting the mpu and assigning middle to be the heading when first turned on
  float mx,y,mz;
  mpu.begin();
  delay(1000); //delay to allow time for accurate reading
  mpu.readMagnetXYZ(&mx,&y,&mz);
  double theta = atan2((y - 33),(mx + 77));
  theta = theta*(180/PI);
  if(theta < 0) {
    theta = -theta;
    float x = 180-theta;
    theta = 180 + x;
  }
  middle = theta;
}

void loop() {
  //read magnetometer
  float mx,my,mz,Rollx,Pitchy,az;
  mpu.readMagnetXYZ(&mx,&my,&mz);
  double theta = atan2((my - 33),(mx + 77));
  theta = theta*(180/PI);
  if(theta < 0) {
    theta = -theta;
    float x = 180-theta;
    theta = 180 + x;
  }
  
  Serial.println(theta);
  float error = theta - middle; //error is how far away you are from the setpoint (middle)
  float speedDifference = error/5 + i/1000 - (error - lastError)/10; //use PID to calculate motor ouput

  /*Serial.print("P: ");
  Serial.print(error/5);
  Serial.print("     ");
  Serial.print("I: ");
  Serial.print(i/1000);
  Serial.print("     ");
  Serial.print("D: ");
  Serial.println((error - lastError)/10);*/
 //Serial.print("speedDiff:  ");
  //Serial.println(speedDifference);
  //Serial.print(mx);
  //Serial.print("     ");
 // Serial.println(my);
  //Serial.println(speedDifference);
  /*Serial.print(mx);
  Serial.print("\t");
  Serial.print(my);
  Serial.print("\t");
  Serial.println(mz);*/
  
  lastError = error; //error is stored in last error


  //Serial.println(speedDifference); //print out the motor output (change in motor speed) for debugging purposes
  
  float rightMotor = max_speed - speedDifference; //assign rightMotor speed
  float leftMotor = max_speed + speedDifference; // assign leftMotor speed

  // constrain the values to be within 0 and the max speed)
  rightMotor = constrain(rightMotor, 0, max_speed);
  leftMotor = constrain(leftMotor, 0, max_speed);
  //Serial.print(rightMotor);
  //Serial.print("      ");
  //Serial.println(leftMotor);
  i += error;
  delay(10);
  /*Serial.print(-leftMotor);
  Serial.print("     ");
  Serial.println(-rightMotor);*/
  drive.setDrive(-leftMotor, -rightMotor); //set the motors

  delay(100); //delay for accurate readings
}

