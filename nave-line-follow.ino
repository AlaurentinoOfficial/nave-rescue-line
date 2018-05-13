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
  // Get all line ir array values
  String lineArray = LineArray();

  // Get lazer distance in front
  uint8_t lazer_distance = Lazer();

  // OBSTACLE
  if(lazer_distance < OBSTACLE_MAX_MM)
  {
    Serial.println("> OBSTACLE");
  }

  // CROSS LINE
  else if(LineCompare(lineArray, "00N00"))
  {
    Serial.print("> CROSS LINE > ");
    Motors.Stop();

    uint8_t colorLeft = Color(COLOR_LEFT); // Measure the color
    uint8_t colorRight = Color(COLOR_RIGHT); // Measure the color
    
    // GREEN - WHITE
    if (colorLeft == COLOR_GREEN && colorRight == COLOR_WHITE)
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
    else
      Motors.MoveFwd(MOVE_POWER[0], MOVE_POWER[1]);
  }

  // BLACK - WHITE
  else if(LineCompare(lineArray, "00111"))
  {
    Serial.println("> BLACK - WHITE");
    Motors.Rotate(COUTER_CLOCKWISE, ROTATE_90_DEGREES_TIME, ROTATE_90_DEGREES_PWR); // Rotate a 90 degrees
  }

  // WHITE - BLACK
  else if(LineCompare(lineArray, "11100"))
  {
    Serial.println("> BLACK - WHITE");
    Motors.Rotate(COUTER_CLOCKWISE, ROTATE_90_DEGREES_TIME, ROTATE_90_DEGREES_PWR); // Rotate a 90 degrees
  }

  // PID
  else
  {
    uint8_t error = CalculateError(lineArray);
    uint8_t pid = PID(error);

    uint8_t left = MOVE_POWER[0] + pid;
    uint8_t right = MOVE_POWER[1] - pid;

    Motors.MoveFwd(left, right);
  }
}

void rescueArea()
{
}
