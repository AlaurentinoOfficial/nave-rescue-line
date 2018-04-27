#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Values.h"

class Sensors
{
public:
  Sensors();
  int* ColorRaw(int port);
  static double Ultrasonic(int port);
};
