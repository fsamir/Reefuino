#ifndef TemperatureSensor_H
#define TemperatureSensor_H
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class TemperatureSensor {
public:
  TemperatureSensor(int sensorPin);
  ~TemperatureSensor();
  double ReadCelsius();


private:
  int _SensorPin;
  double _Compute(int RawADC);
};

#endif



