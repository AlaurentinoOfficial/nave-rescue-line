#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Adafruit_VL53L0X.h>
#include "Values.h"

#define COLOR_WHITE 0
#define COLOR_GREEN 1
#define COLOR_BLACK 2
#define ANY_COLOR -1

Adafruit_VL53L0X distance = Adafruit_VL53L0X();

uint8_t P = 0;
uint8_t I = 0;
uint8_t D = 0;
uint8_t previous_error = 0;

void SensorsSetup()
{
  // Color serndor config
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // Line array config
  pinMode(LINE_ARRAY_LL, INPUT);
  pinMode(LINE_ARRAY_L, INPUT);
  pinMode(LINE_ARRAY_C, INPUT);
  pinMode(LINE_ARRAY_R, INPUT);
  pinMode(LINE_ARRAY_RR, INPUT);
}

void ColorRaw(uint8_t **out, int port)
{
  pinMode(port, INPUT);

  // Get red value
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  out[0] = pulseIn(port, LOW);

  // Get green value
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  out[1] = pulseIn(port, LOW);

  // Get blue value
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  out[2] = pulseIn(port, LOW);
}

uint8_t Color(int port)
{
//  uint8_t* rgb = ColorRaw(port);
//
//  if(rgb[0] < 100 && rgb[1] < 100 && rgb[2] < 100) return COLOR_BLACK;
//  else if(rgb[1] > rgb[0] && rgb[1] > rgb[0]) return COLOR_GREEN;

  return COLOR_WHITE;
}

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

uint8_t PID(uint8_t error)
{
  P = error; // Proportional = Robot position
  I += error; // Integral = Graph Area
  D = error - previous_error; // Derivative = Error Variation (Delta ERROR)
  
  previous_error = error;
  return (uint8_t) (Kp*P) + (Ki*I) + (Kd*D);
}

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

double Lazer()
{
  VL53L0X_RangingMeasurementData_t measure;
  distance.rangingTest(&measure, false); // Pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) // Phase failures have incorrect data
    return -1;

  return measure.RangeMilliMeter;
}
