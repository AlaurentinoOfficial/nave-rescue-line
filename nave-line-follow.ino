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
  Serial.println("Started");
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
  uint8_t lineColors = LineColors();
  uint8_t colorLeft = Color(COLOR_LEFT);
  uint8_t colorRight = Color(COLOR_RIGHT);

  // Verify if there is a obstacle
  if(Lazer() < OBSTACLE_MAX_MM)
  {
    Serial.println("Obstacle detected");
  }
  
  // GREEN - WHITE
  else if (colorLeft == COLOR_GREEN && colorRight == COLOR_WHITE)
  {
    Serial.println("GREEN - WHITE");
    Motors.Rotate(COUTER_CLOCKWISE, ROTATE_90_DEGREES_TIME, ROTATE_90_DEGREES_PWR); // Rotate a 90 degrees
  }

  // WHITE - GREEN
  else if (colorLeft == COLOR_WHITE && colorRight == COLOR_GREEN)
  {
    Serial.println("WHITE - GREEN");
    Motors.Rotate(CLOCKWISE, ROTATE_90_DEGREES_TIME, ROTATE_90_DEGREES_PWR); // Rotate a 90 degrees
  }

  else if(LineCompare(lineColors, "11011") || LineCompare(lineColors, "N000N"))
  {
    Motors.MoveFwd(MOVE_POWER[0], MOVE_POWER[1]);
  }

  else {
    uint8_t error = CalculateError(lineColors);
    uint8_t pid = PID(error);

    uint8_t left = MOVE_POWER[0] - pid;
    uint8_t right = MOVE_POWER[1] + pid;

    Motors.MoveFwd(left, right);
  }
}

void rescueArea()
{
}
