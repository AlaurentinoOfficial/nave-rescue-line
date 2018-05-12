#include "MotorShield.h"

MotorShield::MotorShield(int left1, int left2, int right1, int right2) : motorLeft1(left1), motorLeft2(left2), motorRight1(right1), motorRight2(right2)
{
  this->servo1.attach(9);
  this->servo2.attach(10);
}

static uint8_t MotorShield::PowerLimit(uint8_t power)
{
  if(power > 255) return 255;
  else if(power < 0) return 0;
  else return power;
}

void MotorShield::MoveFwd(uint8_t left, uint8_t right)
{
  left = MotorShield::PowerLimit(left);
  right = MotorShield::PowerLimit(right);

  this->motorLeft1.setSpeed(left);
  this->motorLeft1.run(FORWARD);

  this->motorLeft2.setSpeed(left);
  this->motorLeft2.run(FORWARD);

  this->motorRight1.setSpeed(right);
  this->motorRight1.run(FORWARD);

  this->motorRight2.setSpeed(right);
  this->motorRight2.run(FORWARD);
}

void MotorShield::MoveBwd(uint8_t left, uint8_t right)
{
  left = MotorShield::PowerLimit(left);
  right = MotorShield::PowerLimit(right);
  
  this->motorLeft1.setSpeed(left);
  this->motorLeft1.run(BACKWARD);

  this->motorLeft2.setSpeed(left);
  this->motorLeft2.run(BACKWARD);

  this->motorRight1.setSpeed(right);
  this->motorRight1.run(BACKWARD);

  this->motorRight2.setSpeed(right);
  this->motorRight2.run(BACKWARD);
}

void MotorShield::Rotate(unsigned short direc, uint8_t power, unsigned long delayTime)
{
  this->Stop();
  power = MotorShield::PowerLimit(power);

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
