#ifndef TemperatureSensor_H
#define TemperatureSensor_H

#include <WProgram.h>

class TemperatureSensor {
public:
  TemperatureSensor(byte sensorPin);
  ~TemperatureSensor();
  double ReadCelsius();


private:
  byte _SensorPin;
  double _Compute(int RawADC);
};

#endif



