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
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  pinMode(LINE_ARRAY_LL, INPUT);
  pinMode(LINE_ARRAY_L, INPUT);
  pinMode(LINE_ARRAY_C, INPUT);
  pinMode(LINE_ARRAY_R, INPUT);
  pinMode(LINE_ARRAY_RR, INPUT);
}

int* ColorRaw(int port)
{
  pinMode(port, INPUT);
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  int red = map(pulseIn(port, LOW), 25,72,255,0);

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  int green = map(pulseIn(port, LOW), 30,90,255,0);

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  int blue = map(pulseIn(port, LOW), 25,70,255,0);

  int colors[] = {red, green, blue};
  return colors;
}

uint8_t* Color(int port)
{
  int* rgb = ColorRaw(port);

  if(rgb[0] < 100 && rgb[1] < 100 && rgb[2] < 100) return COLOR_BLACK;
  else if(rgb[1] > rgb[0] && rgb[1] > rgb[0]) return COLOR_GREEN;

  return COLOR_WHITE;
}

uint8_t* LineArray()
{
  uint8_t line[5] = {0, 0, 0, 0, 0};

  line[0] = analogRead(LINE_ARRAY_LL);
  line[1] = analogRead(LINE_ARRAY_L);
  line[2] = analogRead(LINE_ARRAY_C);
  line[3] = analogRead(LINE_ARRAY_R);
  line[4] = analogRead(LINE_ARRAY_RR);

  return line;
}

uint8_t* LineColors()
{
  uint8_t* lineArray = LineArray();
  
  for(int i = 0; i < 5; i++)
  {
    if(lineArray[i] == HIGH) lineArray[i] = COLOR_WHITE;
    else                     lineArray[i] = COLOR_BLACK;
  }

  return lineArray;
}

bool LineCompare(uint8_t* colors, String other)
{
  const char* values = other.c_str();
  bool result = true;

  for(int i = 0; i < 5 && result == true; i++)
  {
    uint8_t value = ANY_COLOR;
    
    if(values[0] == '0') value = COLOR_BLACK;
    else if(values[1] == '1') value = COLOR_WHITE;
    
    if(value != ANY_COLOR)
      result = value == colors[i];
  }

  return result;
}

uint8_t PID(uint8_t error)
{
  P = error; // Proportional = Robot position
  I += error; // Integral = Area
  D = error - previous_error; // Derivative = Error Variation (Delta ERROR)
  
  previous_error = error;
  return (Kp*P) + (Ki*I) + (Kd*D);
}

uint8_t CalculateError(uint8_t* colors)
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
  pinMode(port, OUTPUT);
  digitalWrite(port, LOW);
  delayMicroseconds(2);
  digitalWrite(port, HIGH);
  delayMicroseconds(5);
  digitalWrite(port, LOW);
  pinMode(port, INPUT);
  digitalWrite(port, HIGH);

  double echo = pulseIn(port, HIGH);
  echo = echo * 0.034 /2;

  if(echo > 200.0)
    return 200.0;
  else if(echo < 0.0)
    return 0.0;
  else
    return echo;
}

double Lazer()
{
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  distance.rangingTest(&measure, false); // Pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) // Phase failures have incorrect data
    return -1;

  return measure.RangeMilliMeter;
}
