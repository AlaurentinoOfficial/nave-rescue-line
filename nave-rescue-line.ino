/*
 * ETE Cícero Dias - NAVE Recife
 * Steaph Copyright
 * Authors: Anderson Laurentino
 * 
 * That code is resposable to control the best robot
 * of the OBR and Robocup Jr Rescue Line
 */
#include "Values.h"
#include "MotorShield.h"
#include "Sensors.h"

#define DEBUG true

bool inRescueArea = false;


// **********************
//        SENSORS
// **********************
double lazer = 0.0;

String lineArray = "";

ColorSensor colorLeft;
ColorSensor colorRight;

UltrasonicSensor ultraLeft;
UltrasonicSensor ultraRight;
// **********************


// **********************
//        MOTOR MAP
// **********************
uint8_t motors[4] = {MOTOR_LEFT1, MOTOR_LEFT2, MOTOR_RIGHT1, MOTOR_RIGHT2};
uint8_t servos[3] = {SERVO_TRIGGER_1, SERVO_TRIGGER_2, SERVO_TRIGGER_3};
MotorShield Motors(motors, servos);
// **********************

void setup()
{
	// **********************
	//    SETUP THE SENSORS
	// **********************
	SetupLineArray();
	SetupColor();

	colorLeft.port = COLOR_LEFT;
	colorRight.port = COLOR_RIGHT;

	ultraLeft.port = ULTRA_LEFT;
	ultraRight.port = ULTRA_RIGHT;
	// **********************

	// **********************
	//    SETUP THE MOT0RS
	// **********************
	Motors.Stop();
	// **********************

	Serial.begin(9600);
	Serial.println("steaph/rescue-line/OBR\n\n");
}

void loop()
{
	test();
}

void lineFollow()
{
	lazer = Lazer();
	Color(&colorLeft, &colorRight);
	lineArray = LineArray();

	// **********************
	//       OBSTACLE
	// **********************
	if(lazer > 0 && lazer <= OBSTACLE_MAX_MM)
	{
		Serial.println("> Obstacle detected");

		Motors.Stop();
		ResetPID();

		Ultrasonic(&ultraLeft);
		Ultrasonic(&ultraRight);
	}
	// **********************


	// **********************
	//      GREEN CASES
	// **********************
	else if (colorLeft.color == COLOR_GREEN || colorRight.color == COLOR_GREEN)
	{
		Motors.Stop();
		ResetPID();

		// DOUBLE GREEN
		// DEAD END
		if (colorLeft.color == COLOR_GREEN && colorRight.color == COLOR_GREEN)
		{
			Serial.println("> Double GREEN detected");

			// Rotate 180° degrees at clockwise
			Motors.Rotate(CLOCKWISE, ROTATE_90_DEGREES_PWR, ROTATE_90_DEGREES_TIME * 2);
		}

		// LEFT GREEN
		else if (colorLeft.color == COLOR_GREEN)
		{
			Serial.println("> Left GREEN detected");

			// Rotate 90° degrees couter clockwise
			Motors.Rotate(COUTER_CLOCKWISE, ROTATE_90_DEGREES_PWR, ROTATE_90_DEGREES_TIME);
		}

		// RIGHT GREEN
		else
		{
			Serial.println("> Right GREEN detected");

			// Rotate 90° degrees at clockwise
			Motors.Rotate(CLOCKWISE, ROTATE_90_DEGREES_PWR, ROTATE_90_DEGREES_TIME);
		}
	}
	// **********************


	// **********************
	//      CROSSROADS
	// **********************
	else if (LineCompare(lineArray, "N000N") ||
			 LineCompare(lineArray, "000NN") ||
			 LineCompare(lineArray, "NN000"))
	{
		Motors.Move(MOVE_POWER, MOVE_POWER);
	}
	// **********************


	// **********************
	//          GAP
	// **********************
	else if (LineCompare(lineArray, "11111"))
	{
		Motors.Move(MOVE_POWER, MOVE_POWER);
	}
	// **********************


	// **********************
	//          PID
	// **********************
	else
	{
		// Calculate the pid value
		uint8_t pid_value = PID(CalculateError(lineArray));

		// Move the move according the pid level
		Motors.Move(200 + pid_value, 200 - pid_value);
	}
	// **********************
}

void rescueArea()
{
	// Logic
}

void test()
{
	lineArray = LineArray();
	Color(&colorLeft, &colorRight);

	Serial.println(String("Lines: ") + lineArray);
	Serial.print("Right: "); Serial.print(colorRight.red); Serial.print(", "); +Serial.print(colorRight.green); Serial.print(", "); +Serial.print(colorRight.blue); Serial.print(" | "); Serial.println(colorRight.color);
	Serial.print("Left : "); Serial.print(colorLeft.red); Serial.print(", "); + Serial.print(colorLeft.green); Serial.print(", "); + Serial.print(colorLeft.blue); Serial.print(" | "); Serial.println(colorLeft.color);

	Serial.println("\n");
	delay(300);
}
