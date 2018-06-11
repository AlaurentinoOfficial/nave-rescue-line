/*
 * ETE Cícero Dias - NAVE Recife
 * Steaph Copyright
 * Authors: Anderson Laurentino
 * 
 * That code is resposable to control the best robot
 * of the OBR and Robocup Jr Rescue Line
 */

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
  Servo servo3;

  MotorShield(uint8_t *motors, uint8_t *servos);
  void Move(uint8_t left, uint8_t right);
  void MoveAtTime(uint8_t left, uint8_t right, long delayTime = 0);
  void Rotate(unsigned short direction, uint8_t power, unsigned long delayTime);
  void Stop();
};

