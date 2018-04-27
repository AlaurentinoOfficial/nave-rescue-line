#include "MotorShield.h"

bool inRescueArea = false;

// Motor map
MotorShield Motors(1, 2, 3, 4);

void setup() {
  Serial.begin(9600);

  // Configure the motors
  Motors.Setup();
  Motors.Stop();
}

void loop() {
  if(!inRescueArea)
    lineFollow();
}

void lineFollow() {
  
}
