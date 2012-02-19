#ifndef TemperatureSensor_H
#define TemperatureSensor_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <math.h>

//Reference: http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1260958614
class NTCTemperatureSensor {
public:
	NTCTemperatureSensor(int sensorPin);
	~NTCTemperatureSensor();
	double readCelsius();

private:
	int _sensorPin;
	double _compute(int RawADC);
	double thermister(int RawADC);
};

#endif

