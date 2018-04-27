#include "MotorShield.h"

MotorShield::MotorShield(int left1, int left2, int right1, int right2) : motorLeft1(left1), motorLeft2(left2), motorRight1(right1), motorRight2(right2)
{
}

void MotorShield::Setup()
{
  this->servo1.attach(9);
  this->servo2.attach(10);
}

void MotorShield::MoveFwd(unsigned char left, unsigned char right)
{
  this->motorLeft1.setSpeed(left);
  this->motorLeft1.run(FORWARD);

  this->motorLeft2.setSpeed(left);
  this->motorLeft2.run(FORWARD);

  this->motorRight1.setSpeed(right);
  this->motorRight1.run(FORWARD);

  this->motorRight2.setSpeed(right);
  this->motorRight2.run(FORWARD);
}

void MotorShield::MoveBwd(unsigned char left, unsigned char right)
{
  this->motorLeft1.setSpeed(left);
  this->motorLeft1.run(BACKWARD);

  this->motorLeft2.setSpeed(left);
  this->motorLeft2.run(BACKWARD);

  this->motorRight1.setSpeed(right);
  this->motorRight1.run(BACKWARD);

  this->motorRight2.setSpeed(right);
  this->motorRight2.run(BACKWARD);
}

void MotorShield::Rotate(unsigned short direction, unsigned char power, unsigned long delayTime)
{
  this->Stop();

  this->motorRight1.setSpeed(power);
  this->motorRight2.setSpeed(power);
  this->motorLeft1.setSpeed(power);
  this->motorLeft2.setSpeed(power);

  if (direction == CLOCKWISE)
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
  this->motorLeft1.setSpeed(0x00);
  this->motorLeft1.run(RELEASE);

  this->motorLeft2.setSpeed(0x00);
  this->motorLeft2.run(RELEASE);

  this->motorRight1.setSpeed(0x00);
  this->motorRight1.run(RELEASE);

  this->motorRight2.setSpeed(0x00);
  this->motorRight2.run(RELEASE);
}