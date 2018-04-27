#include "MotorShield.h"
#include "Sensors.h"

bool inRescueArea = false;

// Motor map
//MotorShield Motors(1, 2, 3, 4);

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  // Configure the motors
  //Motors.Setup();
  //Motors.Stop();
}

void loop() {
  if(!inRescueArea)
    lineFollow();
}

void lineFollow() {
  Serial.print(Sensors::Ultrasonic(ULTRA_FRONT));
  Serial.print(", ");
  Serial.println(Sensors::Ultrasonic(ULTRA_LEFT));
  delay(500);
}
