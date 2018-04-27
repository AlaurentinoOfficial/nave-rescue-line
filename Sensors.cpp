#include "Sensors.h"

static double Sensors::Ultrasonic(int port) {
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
