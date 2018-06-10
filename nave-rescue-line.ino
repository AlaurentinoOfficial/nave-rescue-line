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

#define DEBUG false

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
	if(DEBUG)
		test();
	else if(!inRescueArea)
		lineFollow();
	else
		rescueArea();
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
	if(lazer > 0 && lazer <= OBSTACLE_MAX_MM) {
		Serial.println("> Obstacle detected");

		Motors.Stop();
		ResetPID();
    
		double ultrassonicL = Ultrasonic(ULTRA_LEFT);
		double ultrassonicR = Ultrasonic(ULTRA_RIGHT);
	}
	// **********************


	// **********************
	//     DOUBLE GREEN
	//       DEAD END
	// **********************
	else if(colorL == COLOR_GREEN && colorR == COLOR_GREEN) {
		Serial.println("> Double GREEN detected");

		Motors.Stop();
		ResetPID();

		// Rotate 180° degrees at clockwise
		Motors.Rotate(CLOCKWISE, ROTATE_90_DEGREES_PWR, ROTATE_90_DEGREES_TIME * 2);
	}
	// **********************

  
	// **********************
	//      LEFT GREEN
	// **********************
	else if(colorL == COLOR_GREEN) {
		Serial.println("> Left GREEN detected");

		Motors.Stop();
		ResetPID();

		// Rotate 90° degrees couter clockwise
		Motors.Rotate(COUTER_CLOCKWISE, ROTATE_90_DEGREES_PWR, ROTATE_90_DEGREES_TIME);
	}
	// **********************


	// **********************
	//      RIGHT GREEN
	// **********************
	else if(colorR == COLOR_GREEN) {
		Serial.println("> Right GREEN detected");

		Motors.Stop();
		ResetPID();

		// Rotate 90° degrees at clockwise
		Motors.Rotate(CLOCKWISE, ROTATE_90_DEGREES_PWR, ROTATE_90_DEGREES_TIME);
	}
	// **********************


	// **********************
	//      CROSSROADS
	// **********************
	else if (LineCompare(lineArray, "N000N")) {
		Motors.Move(MOVE_POWER, MOVE_POWER);
	}
	// **********************


	// **********************
	//          GAP
	// **********************
	else if (LineCompare(lineArray, "11111")) {
		Motors.Move(MOVE_POWER, MOVE_POWER);
	}
	// **********************


	// **********************
	//          PID
	// **********************
	else {
		uint8_t pid_value = PID(CalculateError(lineArray));

		Motors.Move(MOVE_POWER+pid_value, MOVE_POWER-pid_value);
	}
	// **********************
}

void rescueArea()
{
	// Logic
}

void test() {
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
