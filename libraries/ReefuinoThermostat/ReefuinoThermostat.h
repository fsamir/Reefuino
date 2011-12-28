#ifndef ReefuinoThermostat_H
#define ReefuinoThermostat_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <ReefuinoRelay.h>
#include <TemperatureSensor.h>

class Chronodot;
class DateTime;

class ReefuinoThermostat {
public:
	ReefuinoThermostat(TemperatureSensor ts, ReefuinoRelay chillerRelay,			ReefuinoRelay heaterRelay, double temperatureToKeep);
//	ReefuinoThermostat(TemperatureSensor ts, ReefuinoRelay chillerRelay, ReefuinoRelay heaterRelay, double temperatureToKeep, Chronodot rtc);
	~ReefuinoThermostat();
	float checkTemperature();
	bool isHarmfulTemperature();
	bool isHeating();
	bool isChilling();

private:
	ReefuinoRelay _chillerRelay;
	ReefuinoRelay _heaterRelay;
	TemperatureSensor _temperatureSensor;
	double _tempToKeep;
	DateTime* lastTimeChillerOn;
//	Chronodot clock;
};
#endif
