#ifndef ReefuinoThermostat_H
#define ReefuinoThermostat_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <ReefuinoRelay.h>
#include <TemperatureSensor.h>

enum ThermostatStatus {
	CHILLING = 0, HEATING = 1, COOLINGDOWN = 2, RESTING = 3
};
static String lookup[] = { "CHILLING", "HEATING", "COOLINGDOWN", "RESTING" };

class ReefuinoThermostat {
public:
	ReefuinoThermostat(TemperatureSensor ts, ReefuinoRelay chillerRelay,
			ReefuinoRelay heaterRelay, double temperatureToKeep);
	~ReefuinoThermostat();
	float checkTemperature();
	bool isHarmfulTemperature();
	bool isHeating();
	bool isChilling();
	void ChillerOn();
	ThermostatStatus getStatus();
	String getStatusStr();

private:
	ReefuinoRelay _chillerRelay;
	ReefuinoRelay _heaterRelay;
	TemperatureSensor _temperatureSensor;
	double _tempToKeep;
	ThermostatStatus status;
	void resetCooldown();

};
#endif
