#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

#define ULTRA_FRONT 7
#define ULTRA_LEFT 6
#define ULTRA_RIGHT 5

class Sensors
{
public:
  static double Ultrasonic(int port);
};
