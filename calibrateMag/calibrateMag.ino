#include <math.h>
#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>
#include <IRremote.h>
#include <TECBot_PWMServoDriver.h>
FaBo9Axis mpu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mpu.begin();
  delay(100);
//  float mx, my, mz;
//  mpu.readMagnetXYZ(&mx, &my, &mz);
Serial.println("beginning");

}

void loop() {
  // put your main code here, to run repeatedly:
magcalMPU9250();
}
 void magcalMPU9250() 
 {
 //init variables
 uint16_t ii = 0, sample_count = 0;
 int32_t mag_bias[3] = {0, 0, 0}, mag_scale[3] = {0, 0, 0};
 int16_t mag_max[3] = {0x8000, 0x8000, 0x8000}, mag_min[3] = {0x7FFF, 0x7FFF, 0x7FFF}, mag_temp[3] = {0, 0, 0};
 float x,y,z;
 Serial.println("Mag Calibration: Wave device in a figure eight until done!");
 delay(4000);

 sample_count = 128;
 for(ii = 0; ii < sample_count; ii++) {
 mpu.readMagnetXYZ(&x,&y,&z);
 mag_temp[0] = x;
 mag_temp[1] = y;
 mag_temp[2] = z;  

 for (int jj = 0; jj < 3; jj++) {
  if(mag_temp[jj] > mag_max[jj]) mag_max[jj] = mag_temp[jj]; // create array and find the max/min values to put in it
  if(mag_temp[jj] < mag_min[jj]) mag_min[jj] = mag_temp[jj]; // finds abs max and min
 }
 delay(135);  // at 8 Hz ODR, new mag data is available every 125 ms
 }

// Get hard iron correction
 mag_bias[0]  = (mag_max[0] + mag_min[0])/2;  // get average x mag bias in counts
 mag_bias[1]  = (mag_max[1] + mag_min[1])/2;  // get average y mag bias in counts
 mag_bias[2]  = (mag_max[2] + mag_min[2])/2;  // get average z mag bias in counts

// dest1[0] = (float) mag_bias[0]*MPU9250mRes*MPU9250magCalibration[0];  // save mag biases in G for main program
// dest1[1] = (float) mag_bias[1]*MPU9250mRes*MPU9250magCalibration[1];   
// dest1[2] = (float) mag_bias[2]*MPU9250mRes*MPU9250magCalibration[2];  
Serial.print(mag_bias[0]);
Serial.print("\t");
Serial.print(mag_bias[1]);
Serial.print("\t");
Serial.print(mag_bias[2]);
Serial.println(" ");   
// Get soft iron correction estimate
 mag_scale[0]  = (mag_max[0] - mag_min[0])/2;  // get average x axis max chord length in counts
 mag_scale[1]  = (mag_max[1] - mag_min[1])/2;  // get average y axis max chord length in counts
 mag_scale[2]  = (mag_max[2] - mag_min[2])/2;  // get average z axis max chord length in counts

 float avg_rad = mag_scale[0] + mag_scale[1] + mag_scale[2];
 avg_rad /= 3.0;

// dest2[0] = avg_rad/((float)mag_scale[0]);
// dest2[1] = avg_rad/((float)mag_scale[1]);
// dest2[2] = avg_rad/((float)mag_scale[2]);

 Serial.println("Mag Calibration done!");
 }
