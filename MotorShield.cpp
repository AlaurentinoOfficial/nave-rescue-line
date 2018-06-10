#include "MotorShield.h"

MotorShield::MotorShield(uint8_t *motors, uint8_t *servos) : motorLeft1(motors[0]), motorLeft2(motors[1]), motorRight1(motors[2]), motorRight2(motors[3])
{
  this->servo1.attach(servos[0]);
  this->servo2.attach(servos[1]);
  this->servo3.attach(servos[2]);
}

void MotorShield::Move(uint8_t left, uint8_t right)
{
  left = constrain(left, 0, 255);
  right = constrain(right, 0, 255);

  uint8_t left_dir = left > 0 ? FORWARD : left < 0 ? BACKWARD : RELEASE;
  uint8_t right_dir = right > 0 ? FORWARD : right < 0 ? BACKWARD : RELEASE;

  this->motorLeft1.setSpeed(left);
  this->motorLeft1.run(left_dir);

  this->motorLeft2.setSpeed(left);
  this->motorLeft2.run(left_dir);

  this->motorRight1.setSpeed(right);
  this->motorRight1.run(right_dir);

  this->motorRight2.setSpeed(right);
  this->motorRight2.run(right_dir);
}

void MotorShield::MoveAtTime(uint8_t left, uint8_t right, long delayTime = 0)
{
  this->Move(left, right);

  if(delayTime > 0) {
    delay(delayTime);
    this->Stop();
  }
}

void MotorShield::Rotate(unsigned short direc, uint8_t power, unsigned long delayTime)
{
  this->Stop();
  power = constrain(power, 0, 255);

  this->motorRight1.setSpeed(power);
  this->motorRight2.setSpeed(power);
  this->motorLeft1.setSpeed(power);
  this->motorLeft2.setSpeed(power);

  if (direc == CLOCKWISE)
  {
    this->motorLeft1.run(FORWARD);
    this->motorLeft2.run(FORWARD);
    this->motorRight1.run(BACKWARD);
    this->motorRight2.run(BACKWARD);
  }
  else
  {
    this->motorLeft1.run(BACKWARD);
    this->motorLeft2.run(BACKWARD);
    this->motorRight1.run(FORWARD);
    this->motorRight2.run(FORWARD);
  }

  if(delayTime > 0)
    delay(delayTime);
  
  this->Stop();
}

void MotorShield::Stop()
{
  this->motorLeft1.setSpeed(0);
  this->motorLeft1.run(RELEASE);

  this->motorLeft2.setSpeed(0);
  this->motorLeft2.run(RELEASE);

  this->motorRight1.setSpeed(0);
  this->motorRight1.run(RELEASE);

  this->motorRight2.setSpeed(0);
  this->motorRight2.run(RELEASE);
}
