//Mazerunner - a maze solving robot
//Anish Thite, Jordan Schwartz, and Alex Scotte
// the walls are 12 inches long with a 0.5-1 inch gap between them
#include <TECBot_PWMServoDriver.h>
#include <QTRSensors.h>
TECBot_PWMServoDriver drive = TECBot_PWMServoDriver();

int lastError = 0;
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
short posrow  = 4;
short poscol =  0; 
short heading = 90;
short maze[width][height];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starting Serial Terminal
 //Initialize the PWM controller
  drive.begin();
  drive.setPWMFreq(60);

  delay(1500);
  //Arm the ESC's by sending a "neutral" signal for 1.5 seconds
  Drive(0,0);
  delay(1500);

          //Turn the LED off
//instantiate array
  for (int i = 0; i < width; i++){
   for (int j = 0; j < height; j++){
      maze[i][j] = 0;
    }  
  }
}

void loop() {
//
decide(classifystore());

updatePosition();
delay(1000);
//
//for (int i = 0; i < width; i++){
//   for (int j = 0; j < height; j++){
//      Serial.print(maze[i][j]);
//    }
//    Serial.println(" ");  
//} 





//Serial.print(getinches(leftPingPin, leftEchoPin));
//Serial.print("\t");
//Serial.print(getinches(centerPingPin, centerEchoPin));
//Serial.print("\t");
//Serial.print(getinches(rightPingPin, rightEchoPin));
//Serial.println(" ");
//delay(100);
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
   //Serial.println("got distance");
   return cm;
}
void goforward(){
  float f = getinches(centerPingPin, centerEchoPin);
  float endPoint = f-33;

  while(f > endPoint){
    f = getinches(centerPingPin, centerEchoPin);
    goforward2();
  }
  Drive(0,0);
  
}
void goforward2(){
    // go forward if all sensors are activated or path is already explored
//  if (getinches(centerPingPin,centerEchoPin) > 7 && getinches(leftPingPin,leftEchoPin)< 15 && getinches(rightPingPin,rightEchoPin) < 15){ 
    //if veering left
    if (getinches(leftPingPin,leftEchoPin) < getinches(rightPingPin,rightEchoPin)){
          Drive(10,5);  
    }
    //if veering right
    if (getinches(leftPingPin,leftEchoPin) > getinches(rightPingPin,rightEchoPin)){
          Drive(5,10);
    }
    else{
      Drive(5,5);
    }
 


}
/*float start = getinches(centerPingPin,centerEchoPin);
float endpoint = start - 33;
float f,l,r,lastError,i;
while (f >= endpoint){

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
  Drive(leftMotor,rightMotor);
  delay(100);
  //goes forward to center itself in cell
}
Drive(0,0);*/
//}
//classifies the element and stores it in the array
//classifies: 0: not been there yet 1: only one way up  2: 2 way junction 3: 3 way junction 4: dead end 
int classifystore(){  
  int path = 0;
  if (getinches(leftPingPin,leftEchoPin) > 15){
    path +=1;  
  }
  if (getinches(centerPingPin,centerEchoPin) > 15){
    path +=1;
  }
  if (getinches(rightPingPin,rightEchoPin) > 15){
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
  Serial.println(path);

  return path;
}
void decide(int path){ //potentially can input path
  float f,l,r;
  l = getinches(leftPingPin,leftEchoPin);
  r = getinches(rightPingPin, rightEchoPin);
  f = getinches(centerPingPin, centerEchoPin);
  
  if (path == 1) {
      if(l > 15){turnLeft90(); Serial.println("path is 1, must turn left");}
      else if(r > 15){turnRight90();goforward(); Serial.println("path is 1, must turn right");}
      else if(f > 15){goforward();Serial.println("path is 1, must go forward");}
  }


  
else if (path == 2) {
              if(l < 15){
                if(heading == 0){
                  if(maze[posrow+1][poscol]  == 0){
                    Serial.println("path is 2, heading is 0, must go forward, can't go left");
                    goforward();
                  }
                  else{
                    Serial.println("path is 2, heading is 0, must turn right, can't go left");
                    turnRight90();
//                    goforward();
                    }
                  }
                else if(heading == 90){
                  if(maze[posrow][poscol+1] == 0){
                    Serial.println("path is 2, heading is 90, must go forward, can't go left");
                    goforward();
                  }
                  else{
                    Serial.println("path is 2, heading is 90, must turn right, can't go left");
                    turnRight90();
//                    goforward();
                  }
                }
               else if(heading == 180){
                  if(maze[posrow-1][poscol] == 0){
                    Serial.println("path is 2, heading is 180, must go forward, can't go left");
                    goforward();
                  }
                  else{
                    Serial.println("path is 2, heading is 180, must turn right, can't go left");
                    turnRight90();
//                    goforward();
                  }
               }
              else if(heading == 270){
                if(maze[posrow][poscol-1] == 0){
                  Serial.println("path is 2, heading is 270, must go forward, can't go left");
                  goforward();
                }
                else{
                  Serial.println("path is 2, heading is 270, must turn right, can't go left");
                  turnRight90();
//                  goforward();
                }
              }
              }
          
          
          
              
              else if(r < 15){
                if(heading == 0){
                  if(maze[posrow][poscol-1]  == 0){
                    Serial.println("path is 2, heading is 0, must turn left, can't go right");
                    turnLeft90();
//                    goforward();
                  }
                  else{
                    Serial.println("path is 2, heading is 0, must go forward, can't go right");
                    goforward();
                    }
                  }
                else if(heading == 90){
                  if(maze[posrow+1][poscol] == 0){
                    Serial.println("path is 2, heading is 90, must turn left, can't go right");
                    turnLeft90();
//                    goforward();
                  }
                  else{
                    Serial.println("path is 2, heading is 90, must go forward, can't go right");
                    goforward();
                  }
                }
               else if(heading == 180){
                  if(maze[posrow][poscol+1] == 0){
                    Serial.println("path is 2, heading 180, must turn left, can't go right");
                    turnLeft90();
//                    goforward();
                  }
                  else{
                    Serial.println("path is 2, heading is 180, must go forward, can't go right");
                    goforward();
                  }
               }
              else if(heading == 270){
                if(maze[posrow-1][poscol] == 0){
                  Serial.println("path is 2, heading is 270, must turn left, can't go right");
                  turnLeft90();
//                  goforward();
                }
                else{
                  Serial.println("path is 2, heading is 270, must go forward, can't go right");
                  goforward();
                }
              }
              }
          
                
                
          }
              else if(f < 15){
                if(heading == 0){
                  if(maze[posrow][poscol-1]  == 0){
                    Serial.println("path is 2, heading is 0, must turn left, can't go forward");
                    turnLeft90();
//                    goforward();
                  }
                  else{
                    Serial.println("path is 2, heading is 0, must turn right, can't go forward");
                    turnRight90();
//                    goforward();
                    }
                  }
               else if(heading == 90){
                  if(maze[posrow+1][poscol] == 0){
                    Serial.println("path is 2, heading is 90, must turn left, can't go forward");
                    turnLeft90();
//                    goforward();
                  }
                  else{
                    Serial.println("path is 2, heading is 90, must turn right, can't go forward");
                    turnRight90();
//                    goforward();
                  }
                }
               else if(heading == 180){
                  if(maze[posrow][poscol+1] == 0){
                    Serial.println("path is 2, heading is 180, must turn left, can't go forward");
                    turnLeft90();
//                    goforward();
                  }
                  else{
                    Serial.println("path is 2, heading is 180, must turn right, can't go forward");
                    turnRight90();
//                    goforward();
                  }
               }
              else if(heading == 270){
                if(maze[posrow-1][poscol] == 0){
                  Serial.println("path is 2, heading is 270, must turn left, can't go forward");
                  turnLeft90();
//                  goforward();
                }
                else{
                  Serial.println("path is 2, heading is 270, must turn right, can't go forward");
                  turnRight90();
//                  goforward();
                }
              }
              }
          

       //need to fix the last case
   else if (path == 3) {
      //heading is 0 
      if(heading == 0){
        if(maze[posrow][poscol+1]  == 0){
          Serial.println(" path is 3, heading is 0, turning right (unexplored)");
          turnRight90();
//          goforward();
        }
        else if(maze[posrow+1][poscol] == 0){
          Serial.println(" path is 3, heading is 0, going forward (unexplored)");
          goforward();
          }
        else{
          Serial.println(" path is 3, heading is 0, going forward");
          turnRight90();
//          goforward();
        }
        }
      else if(heading == 90){
        if(maze[posrow-1][poscol] == 0){
          Serial.println(" path is 3, heading is 90, turning right (unexplored)");
          turnRight90();
//          goforward();
        }
        else if(maze[posrow][poscol+1] == 0){
          Serial.println(" path is 3, heading is 90, going forward (unexplored)");
          goforward();
        }
        else{
          Serial.println(" path is 3, heading is 90, turning right");
          turnRight90();
//          goforward();
        }
      }
     else if(heading == 180){
        if(maze[posrow][poscol-1] == 0){
          Serial.println(" path is 3, heading is 180, turning right (unexplored)");
          turnRight90();
//          goforward();
        }
        else if(maze[posrow-1][poscol] == 0){
          Serial.println(" path is 3, heading is 180, goign forward (unexplored)");
          goforward();
        }
        else{
          Serial.println(" path is 3, heading is 180, turning right");
          turnRight90();
//          goforward();
        }
     }
    else if(heading == 270){
      if(maze[posrow+1][poscol] == 0){
        Serial.println(" path is 3, heading is 270, turning right (unexplored)");
        turnRight90();
//        goforward();
      }
      else if(maze[posrow][poscol-1]){
        Serial.println(" path is 3, heading is 270, go forward");
        goforward();
      }
      else{
        Serial.println(" path is 3, heading is 270, turning right");
        turnRight90();
//        goforward();
      }
    }
    }

   else if (path == 4){
      turn180();
   }

}
//void turn()}{
void turnLeft90 (){
  float delayy = 335;// a delay of ___ results in 90 degree turn
  Drive(-30,15);
  delay(delayy);
  Drive(0,0);
  heading += 270;
  goforward();
  if(heading >= 360){
    heading -= 360;
  }
  //Serial.println("turning left");

}
void turn180 (){
  float delayy = 573;// a delay of ___ results in 90 degree turn
  Drive(-30,15);
  delay(delayy);
  Drive(0,0);
  goforward();
  heading += 180;
  if(heading >= 360){
    heading -=360;
  }
  //Serial.println("turning around");

}
void turnRight90 (){
  float delayy = 305;// a delay of ___ results in 90 degree turn
  Drive(30,-15);
  delay(delayy);
  Drive(0,0);
  goforward();
  heading += 90;
  if(heading >=360){
    heading -= 360;
  }
  //Serial.println("turning right");


}
void PIDUltra() {
  int f,l,r,lastError,i;
  l = getinches(leftPingPin,leftEchoPin);
  r = getinches(rightPingPin, rightEchoPin);
  f = getinches(centerPingPin, centerEchoPin);

  int error = l - r;
  
  int speedDifference = error/5 + i + (error - lastError);
  lastError = error;
  int rightMotor = max_speed + speedDifference;
  int leftMotor = max_speed - speedDifference;
  rightMotor = constrain(rightMotor,0,max_speed);
  leftMotor = constrain(leftMotor,0,max_speed);
  i += error;
  Drive(leftMotor,rightMotor);
  delay(100);
}
void updatePosition(){
  if(heading == 0){
    posrow++;
  }
  if(heading == 90){
    poscol++;
  }
  if(heading == 180){
    posrow--;
  }
  if(heading == 270){
    poscol--;
  }
  
}
void Drive(int i, int j){
  Drive(i,j);
}

