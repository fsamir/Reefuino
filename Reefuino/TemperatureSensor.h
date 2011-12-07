#ifndef TemperatureSensor_H
#define TemperatureSensor_H

#include <WProgram.h> //It is very important to remember this!

class TemperatureSensor {
public:
  TemperatureSensor(int pin);
  ~TemperatureSensor();
  void Read();
  void off();
  //void blink(int time);
};

#endif


