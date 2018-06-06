/*
 * ETE Cícero Dias - NAVE Recife
 * Steaph Copyright
 * Authors: Anderson Laurentino
 * 
 * That code is resposable to control the best robot
 * of the OBR and Robocup Jr Rescue Line
 */

#include "MotorShield.h"
#include "Sensors.h"

bool inRescueArea = false;

// Motor map
MotorShield Motors(MOTOR_LEFT1, MOTOR_LEFT2, MOTOR_RIGHT1, MOTOR_RIGHT2);

void setup()
{
  // Setup the sensors
  SensorsSetup();

  // Configure the motors
  Motors.Stop();

  Serial.begin(9600);
  Serial.println("steaph/LineFolow-Rescue/OBR\n\n");
}

void loop()
{
  if(!inRescueArea)
    lineFollow();
  else
    rescueArea();
}

void lineFollow()
{
  // Logic
}

void rescueArea()
{
  // Logic
}
