#ifndef ThreeStagesThermostat_H
#define ThreeStagesThermostat_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <ReefuinoRelay.h>
#include <TemperatureSensor.h>

#include <Chronodot.h>

#include "Time.h"
#include "TimeAlarms.h"

//class Chronodot;
class DateTime;

/**
 * This is the most advanced of all thermostats and controls three devices with the main aim to save electric energy.
 *
 * Logic:
 * If the temperature raises above the desired temperature (26C) it turns on the fans.
 * If the temperature keeps going up with the fans on, then the chiller turns on at 26.6C.
 * On the other hand, when the temperature goes below 25.5 it activates the heater.
 *
 * In addition, if the temperature goes up to a harmful level (29C) it triggers an alarm that can sound a buzzer,
 * send emails or send SMS(to be implemented)
 *
 * Finally, all devices have a delay before getting activate in order to avoid frequent restarts due to small
 * temperature fluctuations and end up burning the device or consuming too much energy
 *
 */
class ThreeStagesThermostat  {
public:
	ThreeStagesThermostat(TemperatureSensor ts, ReefuinoRelay chillerRelay,
			ReefuinoRelay heaterRelay, ReefuinoRelay fanRelay, double temperatureToKeep,
			Chronodot clock);
	~ThreeStagesThermostat();
	float checkTemperature();
	bool isHarmfulTemperature();
	bool isHeating();
	bool isChilling();
	bool isVentilating();
	void ChillerOn();

private:
	ReefuinoRelay _chillerRelay;
	ReefuinoRelay _fanRelay;
	ReefuinoRelay _heaterRelay;
	TemperatureSensor _temperatureSensor;
	double _tempToKeep;
	DateTime lastTimeChillerOn;
	Chronodot clock;

};
#endif
