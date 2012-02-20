#ifndef TemperatureSensor_H
#define TemperatureSensor_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <OneWire.h>
#include <DallasTemperature.h>

class OneWireTemperatureSensor {
public:
	OneWireTemperatureSensor(int sensorPin);
	~OneWireTemperatureSensor();
	void init();
	float readCelsius();
	float readCelsius(uint8_t deviceIndex);

private:
	int _sensorPin;
	float _compute(int RawADC);
	OneWire oneWire;
	DallasTemperature sensors;
//	DeviceAddress insideThermometer, outsideThermometer;

};

#endif

