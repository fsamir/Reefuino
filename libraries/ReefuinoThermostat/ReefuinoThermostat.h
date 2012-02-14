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
	CHILLING = 0,
	HEATING = 1,
	WAITING = 2,
	RESTING = 3,
	CHILLING_WARN = 4,
	HEATING_WARN = 5
};

static String lookup[] = { "CHILLING", "HEATING", "WAITING", "RESTING",
"CHILLING_WARN", "HEATING_WARN" };


class ReefuinoThermostat {

public:
	ReefuinoThermostat(TemperatureSensor ts, ReefuinoRelay chillerRelay,
	ReefuinoRelay heaterRelay, double temperatureToKeep);
	~ReefuinoThermostat();
	float checkTemperature();
	bool isHeating();
	bool isChilling();
	ThermostatStatus getStatus();
	String getStatusStr();
	long getSecondsRemainingForNextActivation();
	long getLastActivationTime();
	bool isHarmfulTemperature();

private:
	ReefuinoRelay _chillerRelay;
	ReefuinoRelay _heaterRelay;
	TemperatureSensor _temperatureSensor;
	double _tempToKeep;
	ThermostatStatus status;
	void resetActivationTimmer();
	void checkHarmfulOperationTime();

	ReefuinoThermostat(TemperatureSensor ts, ReefuinoRelay chillerRelay,
			ReefuinoRelay heaterRelay, double temperatureToKeep);
	~ReefuinoThermostat();
	float checkTemperature();
	bool isHeating();
	bool isChilling();
	ThermostatStatus getStatus();
	String getStatusStr();
	long getSecondsRemainingForNextActivation();
	long getLastActivationTime();
	bool isHarmfulTemperature();
	bool isWorkingTooLong();
};

#endif
