#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

#include <Servo.h>
#include <AFMotor.h>

#define CLOCKWISE 0
#define COUTER_CLOCKWISE 1

class MotorShield
{
public:
  AF_DCMotor motorRight1;
  AF_DCMotor motorRight2;
  AF_DCMotor motorLeft1;
  AF_DCMotor motorLeft2;
  Servo servo1;
  Servo servo2;

  MotorShield(int left1, int left2, int right1, int right2);
  void Setup();
  void MoveFwd(uint8_t left, uint8_t right);
  void MoveBwd(uint8_t left, uint8_t right);
  void Rotate(unsigned short direction, unsigned char power, unsigned long delayTime);
  void Stop();
};
