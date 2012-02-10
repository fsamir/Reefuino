#ifndef TemperatureSensor_H
#define TemperatureSensor_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <math.h>

//Reference: http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1260958614
class TemperatureSensor {
public:
	TemperatureSensor(int sensorPin);
	~TemperatureSensor();
	float readCelsius();

private:
	int _sensorPin;
	float _compute(int RawADC);
};

#endif

