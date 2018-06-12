/*
 * ETE Cícero Dias - NAVE Recife
 * Steaph Copyright
 * Authors: Anderson Laurentino
 * 
 * That code is resposable to control the best robot
 * of the OBR and Robocup Jr Rescue Line
 */

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Adafruit_VL53L0X.h>

#define COLOR_WHITE 0
#define COLOR_GREEN 1
#define COLOR_BLACK 2
#define ANY_COLOR -1

// **********************
//   SETUP THE SENSORS
// **********************
void SetupSensors()
{
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);
	pinMode(COLOR_LEFT, INPUT);
	pinMode(COLOR_RIGHT, INPUT);
  
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);
  
	pinMode(LINE_ARRAY_LL, INPUT);
	pinMode(LINE_ARRAY_L, INPUT);
	pinMode(LINE_ARRAY_C, INPUT);
	pinMode(LINE_ARRAY_R, INPUT);
	pinMode(LINE_ARRAY_RR, INPUT);
}
// **********************


// **********************
//      RGB COLOR
// **********************
typedef struct __attribute__((packed)) {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} RGB;

// Mesuare the RGB color in the sensor
void ColorRaw(RGB * color, uint8_t port)
{ 
	// Get red value
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	color->red = pulseIn(port, LOW);
  
	// Get green value
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	color->green = pulseIn(port, LOW);
  
	// Get blue value
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	color->blue = pulseIn(port, LOW);
}

// Analyze the colors and try distinguish the color
uint8_t Color(int port)
{
	RGB color;
	ColorRaw(&color, port);

	if(color.red > 120 && color.green > 120 && color.blue > 120) return COLOR_BLACK;
	else if(color.green - color.red > 20 && color.green - color.blue > 20) return COLOR_GREEN;

	return COLOR_WHITE;
}
// **********************


// **********************
//     IR LINE ARRAY
// **********************
// Get last value of the IR sensors
String LineArray()
{
	String result;

	result += digitalRead(LINE_ARRAY_LL) == HIGH ? "1" : "0";
	result += digitalRead(LINE_ARRAY_L) == HIGH ? "1" : "0";
	result += digitalRead(LINE_ARRAY_C) == HIGH ? "1" : "0";
	result += digitalRead(LINE_ARRAY_R) == HIGH ? "1" : "0";
	result += digitalRead(LINE_ARRAY_RR) == HIGH ? "1" : "0";

	return result;
}

// Compare twice ir line arrays
bool LineCompare(String colors, String other)
{
	const char* lines = colors.c_str();
	const char* values = other.c_str();
	bool result = true;

	for(int i = 0; i < 5 && result == true; i++)
	{
		if(values[i] == '0' || values[i] == '1')
			result = values[i] == lines[i];
	}

	return result;
}
// **********************


// **********************
//          PID
// **********************
uint8_t P = 0;
uint8_t I = 0;
uint8_t D = 0;
uint8_t previous_error = 0;

// PID Function
uint8_t PID(uint8_t error)
{
	P = error; // Proportional = Robot position
	I += error; // Integral = Graph Area
	D = error - previous_error; // Derivative = Error Variation (Delta ERROR)
  
	previous_error = error;
	return (uint8_t) (Kp*P) + (Ki*I) + (Kd*D);
}

void ResetPID()
{
	P = 0;
	I = 0;
	D = 0;
	previous_error = 0;
}

// Measure the error
uint8_t CalculateError(String lineArray)
{
		   if(LineCompare(lineArray, "11110")) return 4;
	else if(LineCompare(lineArray, "11100")) return 3;
	else if(LineCompare(lineArray, "11101")) return 2;
	else if(LineCompare(lineArray, "11001")) return 1;
	else if(LineCompare(lineArray, "11011")) return 0;
	else if(LineCompare(lineArray, "10011")) return -1;
	else if(LineCompare(lineArray, "10111")) return -2;
	else if(LineCompare(lineArray, "00111")) return -3;
	else if(LineCompare(lineArray, "01111")) return -4;
	else return 3;
}
// **********************


// **********************
//          LAZER
// **********************
Adafruit_VL53L0X distance = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure;

double Lazer()
{
	// Pass in 'true' to get debug data printout!
	distance.rangingTest(&measure, false);

	// Phase failures have incorrect data
	if (measure.RangeStatus != 4)
		return -1;

	return measure.RangeMilliMeter;
}
// **********************


// **********************
//       ULTRASONIC
// **********************
double Ultrasonic(int port)
{
	// Send trigger
	pinMode(port, OUTPUT);
	digitalWrite(port, LOW);
	delayMicroseconds(2);
	digitalWrite(port, HIGH);
	delayMicroseconds(5);
	digitalWrite(port, LOW);
	pinMode(port, INPUT);
	digitalWrite(port, HIGH);

	// Mesuare
	double echo = pulseIn(port, HIGH);
	echo = echo * 0.034 /2;

	// Create limit
	return constrain(echo, 0, 200);
}
// **********************
