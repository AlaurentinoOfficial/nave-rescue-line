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
	SetupSensors();
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
	double lazer = Lazer();
	uint8_t colorL = Color(COLOR_LEFT);
	uint8_t colorR = Color(COLOR_RIGHT);
	String lineArray = LineArray();

	// **********************
	//       OBSTACLE
	// **********************
	if(lazer > 0 && lazer <= OBSTACLE_MAX_MM)
	{
		Serial.println("> Obstacle detected");

		Motors.Stop();
		ResetPID();

		if (Ultrasonic(ULTRA_LEFT) > Ultrasonic(ULTRA_RIGHT))
		{
		}
		else
		{
		}
	}
	// **********************


	// **********************
	//      GREEN CASES
	// **********************
	else if (colorL == COLOR_GREEN || colorR == COLOR_GREEN)
	{
		Motors.Stop();
		ResetPID();

		// DOUBLE GREEN
		// DEAD END
		if (colorL == COLOR_GREEN && colorR == COLOR_GREEN)
		{
			Serial.println("> Double GREEN detected");

			// Rotate 180° degrees at clockwise
			Motors.Rotate(CLOCKWISE, ROTATE_90_DEGREES_PWR, ROTATE_90_DEGREES_TIME * 2);
		}

		// LEFT GREEN
		else if (colorL == COLOR_GREEN)
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
	String lineArray = LineArray();

	RGB colorL; ColorRaw(&colorL, COLOR_LEFT);
	RGB colorR; ColorRaw(&colorR, COLOR_RIGHT);
	uint8_t colorLV = Color(COLOR_LEFT);
	uint8_t colorRV = Color(COLOR_RIGHT);

	Serial.println(String("Lines: ") + lineArray);
	Serial.print("Right: "); Serial.print(colorR.red); Serial.print(", "); +Serial.print(colorR.green); Serial.print(", "); +Serial.print(colorR.blue); Serial.print(" | "); Serial.println(colorRV);
	Serial.print("Left : "); Serial.print(colorL.red); Serial.print(", "); + Serial.print(colorL.green); Serial.print(", "); + Serial.print(colorL.blue); Serial.print(" | "); Serial.println(colorLV);

	Serial.println("\n");
	delay(300);
}
