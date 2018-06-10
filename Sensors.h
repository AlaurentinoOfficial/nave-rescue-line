#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Adafruit_VL53L0X.h>


// **********************
//     IR LINE ARRAY
// **********************
#define COLOR_WHITE 0
#define COLOR_GREEN 1
#define COLOR_BLACK 2
#define ANY_COLOR -1

// Mesuare the RGB color in the sensor
uint8_t **ColorRaw(int port)
{
  pinMode(port, INPUT);
  
  uint8_t *out;

  // Get red value
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  out[0] = map(pulseIn(port, LOW), 25,72,255,0);

  // Get green value
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  out[1] = map(pulseIn(port, LOW), 30,90,255,0);

  // Get blue value
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  out[2] = map(pulseIn(port, LOW), 25,70,255,0);
  
  return &out;
}

// Analyze the colors and try distinguish the color
uint8_t Color(int port)
{
  uint8_t* rgb = *ColorRaw(port);

  if(rgb[0] < 100 && rgb[1] < 100 && rgb[2] < 100) return COLOR_BLACK;
  else if(rgb[1] > rgb[0] && rgb[1] > rgb[0]) return COLOR_GREEN;

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

// Measure the error
uint8_t CalculateError(String colors)
{
       if(LineCompare(colors, "11110")) return 4;
  else if(LineCompare(colors, "11100")) return 3;
  else if(LineCompare(colors, "11101")) return 2;
  else if(LineCompare(colors, "11001")) return 1;
  else if(LineCompare(colors, "11011")) return 0;
  else if(LineCompare(colors, "10011")) return -1;
  else if(LineCompare(colors, "10111")) return -2;
  else if(LineCompare(colors, "00111")) return -3;
  else if(LineCompare(colors, "01111")) return -4;
  else return 5;
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
  return echo > 200.0 ? 200.0 : echo < 0.0 ? 0.0 : echo;
}
// **********************
