#include "Values.h"
#include "MotorShield.h"
#include "Sensors.h"

bool inRescueArea = false;

// Motor map
MotorShield Motors(MOTOR_LEFT1, MOTOR_LEFT2, MOTOR_RIGHT1, MOTOR_RIGHT2);

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  // Sutup the sensors
  SensorsSetup();

  // Configure the motors
  Motors.Stop();
}

void loop() {
  if(!inRescueArea)
    lineFollow();
}

void lineFollow() {
  Serial.println(Ultrasonic(7));
  delay(500);
}
