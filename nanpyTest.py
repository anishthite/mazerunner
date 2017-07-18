from nanpy import ArduinoApi,SerialManager
from nanpy import wire
from time import sleep
import math

print("start")
connection = SerialManager(device = '/dev/cu.usbmodem1421')
print("connection variabel")
a = ArduinoApi(connection = connection)
print("connection achieved")
w = wire.Wire(connection = connection)
w.begin()
print("wire began!!!")


PWM_CENTER = 320
PWM_MIN  = 180
PWM_MAX = 560
DEADBAND = 20
_i2caddr = 0x40

PCA9685_SUBADR1 = 0x2
PCA9685_SUBADR2 = 0x3
PCA9685_SUBADR3 = 0x4

PCA9685_MODE1 = 0x0
PCA9685_PRESCALE = 0xFE

LED0_ON_L = 0x6
LED0_ON_H = 0x7
LED0_OFF_L = 0x8
LED0_OFF_H = 0x9

ALLLED_ON_L = 0xFA
ALLLED_ON_H = 0xFB
ALLLED_OFF_L = 0xFC
ALLLED_OFF_H = 0xFD

def setDrive(a,b):
  setMotor(0,a)
  setMotor(1,b)

def setMotor(num, speed):
  speed = constrain(speed, -100, 100)
  setPWM(num, 0, eliminateDeadband(speed))

def setPWM(num, on, off):
  w.beginTransmission(_i2caddr)
  print("began transmission")
  w.write(LED0_ON_L+4*num)
  print("wrote")
  w.write(on)
  w.write(on>>8)
  w.write(off)
  w.write(off>>8)
  w.endTransmission()
  print("ended transmission")


def eliminateDeadband(speed):
  if (speed == 0):
    return PWM_CENTER
  elif (speed < 0):
    return int(map(speed, -100, 0, PWM_MIN, PWM_CENTER - DEADBAND))
  else:
    return int(map(speed, 0, 100, PWM_CENTER + DEADBAND, PWM_MAX))

def setPWMFreq(freq):
  freq *= 0.9
  prescaleval = 25000000
  prescaleval /= 4096
  prescaleval /= freq
  prescaleval -= 1
                                                                   
  prescale = math.floor(prescaleval + 0.5)

  oldmode = read8(PCA9685_MODE1)
  newmode = (oldmode&0x7F) | 0x10
  write8(PCA9685_MODE1, newmode)
  write8(PCA9685_PRESCALE, prescale)
  write8(PCA9685_MODE1, oldmode)
  sleep(0.005)
  write8(PCA9685_MODE1, oldmode | 0xa1)


def write8(addr, d):
  w.beginTransmission(_i2caddr)
  w.write(addr)
  w.write(d)
  w.endTransmission()


def read8(addr):
  w.beginTransmission(_i2caddr)
  w.write(addr)
  w.endTransmission()

  w.requestFrom(_i2caddr, 1)
  return w.read()

def constrain(val, min_val, max_val):
    if val < min_val: return min_val
    if val > max_val: return max_val
    return val

def begin():
  write8(PCA9685_MODE1, 0x0)

def map(x, in_min, in_max, out_min, out_max):
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

def setServo(num, position):
  position = constrain(position, 0, 180)
  pwmVal = int(map(position, 0, 180, PWM_MIN, PWM_MAX))
  setPWM(num, 0, pwmVal)



begin()
setPWMFreq(60)
setDrive(0,0)
sleep(1.5)
setServo(5,180)
sleep(1)
setServo(5,0)
sleep(1)
setServo(4,0)
sleep(1)
setServo(4,180)

print("finished")
  
  
