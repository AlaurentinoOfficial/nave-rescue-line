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
//      RGB COLOR
// **********************
typedef struct __attribute__((packed)) {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t color;
	uint8_t port;
} ColorSensor;

void SetupColor()
{
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	digitalWrite(S0, HIGH);
	digitalWrite(S1, LOW);
}

// Mesuare the RGB color in the sensor
void ColorRaw(ColorSensor * s1, ColorSensor * s2)
{ 
	pinMode(s1->port, INPUT);
	pinMode(s2->port, INPUT);

	// Get red value
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	s1->red = pulseIn(s1->port, LOW);
	s2->red = pulseIn(s2->port, LOW);
  
	// Get green value
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	s1->green = pulseIn(s1->port, LOW);
	s2->green = pulseIn(s2->port, LOW);
  
	// Get blue value
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	s1->blue = pulseIn(s1->port, LOW);
	s2->blue = pulseIn(s2->port, LOW);
}

// Analyze the colors and try distinguish the color
void Color(ColorSensor * s1, ColorSensor * s2)
{
	ColorRaw(s1, s2);

	s1->color = COLOR_WHITE;
	s2->color = COLOR_WHITE;
}
// **********************


// **********************
//     IR LINE ARRAY
// **********************
void SetupLineArray()
{
	pinMode(LINE_ARRAY_LL, INPUT);
	pinMode(LINE_ARRAY_L, INPUT);
	pinMode(LINE_ARRAY_C, INPUT);
	pinMode(LINE_ARRAY_R, INPUT);
	pinMode(LINE_ARRAY_RR, INPUT);
}

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
typedef struct __attribute__((packed)) {
	uint8_t distance;
	uint8_t port;
} UltrasonicSensor;

void Ultrasonic(UltrasonicSensor * s1)
{
	// Send trigger
	pinMode(s1->port, OUTPUT);
	digitalWrite(s1->port, LOW);
	delayMicroseconds(2);
	digitalWrite(s1->port, HIGH);
	delayMicroseconds(5);
	digitalWrite(s1->port, LOW);
	pinMode(s1->port, INPUT);
	digitalWrite(s1->port, HIGH);

	// Mesuare
	s1->distance = constrain(pulseIn(s1->port, HIGH) * 0.034 / 2, 0, 200);
}
// **********************
