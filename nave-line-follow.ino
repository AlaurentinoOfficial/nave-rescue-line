#include "MotorShield.h"
#include "Sensors.h"

bool inRescueArea = false;

// Motor map
MotorShield Motors(MOTOR_LEFT1, MOTOR_LEFT2, MOTOR_RIGHT1, MOTOR_RIGHT2);

void setup() {
  // Setup the sensors
  SensorsSetup();

  // Configure the motors
  Motors.Stop();

  Serial.begin(9600);
  Serial.println("Started");
}

void loop() {
  if(!inRescueArea)
    lineFollow();
}

void lineFollow() {
  unsigned short colorLeft = Color(COLOR_LEFT);
  unsigned short colorRight = Color(COLOR_RIGHT);
  double ultra_front = Ultrasonic(ULTRA_FRONT);

  // Verify if there is a obstacle
  if(ultra_front < 10)
  {
    Serial.println("Obstacle detected");
  }

  // WHITE - WHITE
  // BLACK - BLACK
  // GREEN - GREEN
  else if((colorLeft == COLOR_WHITE && colorRight == COLOR_WHITE)
  || (colorLeft == COLOR_BLACK && colorRight == COLOR_BLACK)
  || (colorLeft == COLOR_GREEN && colorRight == COLOR_GREEN))
  {
    Motors.MoveFwd(MOVE_POWER[0], MOVE_POWER[1]);
  }

  // BLACK - WHITE
  else if(colorLeft == COLOR_BLACK && colorRight == COLOR_WHITE)
  {
    Serial.println("BLACK - WHITE");
    Motors.MoveFwd(BLACK_WHITE[0], BLACK_WHITE[1]);
  }

  // WHITE - BLACK
  else if(colorLeft == COLOR_WHITE && colorRight == COLOR_BLACK)
  {
    Serial.println("WHITE - BLACK");
    Motors.MoveFwd(WHITE_BLACK[0], WHITE_BLACK[1]);
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

  delay(500);
}
