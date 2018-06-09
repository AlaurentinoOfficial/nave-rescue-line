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
  double lazer = Lazer();
  double ultrassonicL = Ultrasonic(ULTRA_LEFT);
  double ultrassonicR = Ultrasonic(ULTRA_RIGHT);

  String lineArray = LineArray();
  uint8_t* colorL = *ColorRaw(COLOR_LEFT);
  uint8_t* colorR = *ColorRaw(COLOR_RIGHT);

  Serial.println(String("Lazer: ") + String(lazer));
  Serial.println(String("Ultrassonic left: ") + String(ultrassonicL));
  Serial.println(String("Ultrassonic right: ") + String(ultrassonicR));

  Serial.println("Line Array: " + lineArray);
  Serial.println(String("Color Left: ") + String(colorL[0]) + " " + String(colorL[1]) + " " + String(colorL[2]));
  Serial.println(String("Color Right: ") + String(colorR[0]) + " " + String(colorR[1]) + " " + String(colorR[2]));

  Serial.println("\n");
  delay(3000);
}

void rescueArea()
{
  // Logic
}
