#include "ThreeStagesThermostat.h"
#include "TemperatureSensor.h"
#include "ReefuinoRelay.h"
#include "Time.h"
#include "TimeAlarms.h"

double actionBuffer = 0.5;
double harmfullFactor = 1.5;

bool isOn = false;

//Chronodot clock;

ThreeStagesThermostat::ThreeStagesThermostat(TemperatureSensor ts,
		ReefuinoRelay chillerRelay, ReefuinoRelay heaterRelay, ReefuinoRelay fanRelay,
		double temperatureToKeep, Chronodot rtc) :
		_tempToKeep(temperatureToKeep), _temperatureSensor(ts), _chillerRelay(
				chillerRelay), _heaterRelay(heaterRelay), _heaterRelay(heaterRelay), clock(clock) {
}


//<<destructor>>
ThreeStagesThermostat::~ThreeStagesThermostat() {/*nothing to destruct*/
}

float ThreeStagesThermostat::checkTemperature() {
	float temp = _temperatureSensor.readCelsius(); // read ADC and  convert it to Celsius
	if (temp >= (_tempToKeep + actionBuffer)) {

//		AlarmId chillerOnTimmer = Alarm.timerOnce(10, ChillerOn);	    // called once after 10 seconds
		Alarm.timerOnce(10, _chillerRelay.turnOn); // called once after 10 seconds

//		Alarm.timerOnce(10, this->ChillerOn); // called once after 10 seconds
//		Alarm.timerOnce(10, _chillerRelay.turnOn);	    // called once after 10 seconds
//		_chillerRelay.turnOn();

//		if (lastTimeChillerOn == NULL || lastTimeChillerOn) {
//			_chillerRelay.turnOn();
//			lastTimeChillerOn = clock.now();
//		}
	}
	if (temp <= _tempToKeep) {
		_chillerRelay.turnOff();
	}
	if (temp < (_tempToKeep - actionBuffer)) {
		_heaterRelay.turnOn();
	}
	if (temp >= _tempToKeep) {
		_heaterRelay.turnOff();
	}

	Alarm.delay(100);
	return temp;
}

/*Is the temperature dangerously high or low? */
bool ThreeStagesThermostat::isHarmfulTemperature() {
	double temp = _temperatureSensor.readCelsius();
	if (temp >= _tempToKeep + harmfullFactor
			|| temp <= _tempToKeep - harmfullFactor) {
		return true;
	} else {
		return false;
	}
}

bool ThreeStagesThermostat::isHeating() {
	return _heaterRelay.isOn();
}

bool ThreeStagesThermostat::isChilling() {
	return _chillerRelay.isOn();
}

void ThreeStagesThermostat::ChillerOn() {
	_chillerRelay.turnOn();
}
