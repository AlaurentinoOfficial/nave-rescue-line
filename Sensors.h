#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Values.h"

#define COLOR_WHITE 0
#define COLOR_GREEN 1
#define COLOR_BLACK 2

void SensorsSetup()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
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

unsigned short Color(int port)
{
  int* rgb = ColorRaw(port);

  if(rgb[0] < 100 && rgb[1] < 100 && rgb[2] < 100)
    return COLOR_BLACK;
  else if(rgb[1] > rgb[0] && rgb[1] > rgb[0])
    return COLOR_GREEN;

  return COLOR_WHITE;
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
