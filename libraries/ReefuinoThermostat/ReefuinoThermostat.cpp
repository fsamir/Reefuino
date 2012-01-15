#include "ReefuinoThermostat.h"
#include "TemperatureSensor.h"
#include "ReefuinoRelay.h"
#include "Time.h"
#include "TimeAlarms.h"

double actionBuffer = 0.5;
double harmfullFactor = 1.5;

bool isOn = false;

//Simple timmer
//http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1233872134/all
//static unsigned long DELAY = 60000L; //1min
static unsigned long DELAY = 6000L; //6 seconds
unsigned long nextSwitchTime = millis() + DELAY;
bool isWaitingForCooldown = false;

//Chronodot clock;

ReefuinoThermostat::ReefuinoThermostat(TemperatureSensor ts,
		ReefuinoRelay chillerRelay, ReefuinoRelay heaterRelay,
		double temperatureToKeep, Chronodot rtc) :
		_tempToKeep(temperatureToKeep), _temperatureSensor(ts), _chillerRelay(
				chillerRelay), _heaterRelay(heaterRelay), clock(clock) {
	status = RESTING;
}

ReefuinoThermostat::ReefuinoThermostat(TemperatureSensor ts,
		ReefuinoRelay chillerRelay, ReefuinoRelay heaterRelay,
		double temperatureToKeep) :
		_tempToKeep(temperatureToKeep), _temperatureSensor(ts), _chillerRelay(
				chillerRelay), _heaterRelay(heaterRelay) {
	status = RESTING;
}

//<<destructor>>
ReefuinoThermostat::~ReefuinoThermostat() {/*nothing to destruct*/
}

float ReefuinoThermostat::checkTemperature() {
	float temp = _temperatureSensor.readCelsius(); // read ADC and  convert it to Celsius
	//Check whether it should wait or the cooldown period has expired
	Serial.print("nextSwitchTime: ");
	Serial.println(nextSwitchTime);

	Serial.print("milis: ");
	Serial.println(millis());

	if (nextSwitchTime < millis()) {
		resetCooldown();
	} else {
		Serial.println("activating cooldown");
		isWaitingForCooldown = true;
		status = COOLINGDOWN;
	}
	if (temp >= (_tempToKeep + actionBuffer)) {
		if (!isWaitingForCooldown) {
			_chillerRelay.turnOn();
			status = CHILLING;
		}else{
			Serial.println("hot but waiting");
		}
	}
	if (temp <= _tempToKeep) {
		if (_chillerRelay.isOn() && !isWaitingForCooldown) {
			_chillerRelay.turnOff();
			status = RESTING;
		}else{
			Serial.println("not hot but waiting");
		}
	}
	if (temp < (_tempToKeep - actionBuffer)) {
		if (!isWaitingForCooldown) {
			_heaterRelay.turnOn();
			status = HEATING;
		}else{
			Serial.println("cold but waiting");
		}
	}
	if (temp >= _tempToKeep) {
		if (!isWaitingForCooldown) {
			_heaterRelay.turnOff();
			status = RESTING;
		}else{
			Serial.println("resting but waiting");
		}
	}

//	Alarm.delay(100);
	return temp;
}

/*Is the temperature dangerously high or low? */
bool ReefuinoThermostat::isHarmfulTemperature() {
	double temp = _temperatureSensor.readCelsius();
	if (temp >= _tempToKeep + harmfullFactor
			|| temp <= _tempToKeep - harmfullFactor) {
		return true;
	} else {
		return false;
	}
}

bool ReefuinoThermostat::isHeating() {
	return _heaterRelay.isOn();
}

bool ReefuinoThermostat::isChilling() {
	return _chillerRelay.isOn();
}

void ReefuinoThermostat::ChillerOn() {
	_chillerRelay.turnOn();
}
ThermostatStatus ReefuinoThermostat::getStatus() {
	status;
}

String ReefuinoThermostat::getStatusStr() {
	return lookup[status];
}

void ReefuinoThermostat::resetCooldown() {
	Serial.println("resetting cooldown");
	nextSwitchTime = millis() + DELAY;
	isWaitingForCooldown = false;
}
