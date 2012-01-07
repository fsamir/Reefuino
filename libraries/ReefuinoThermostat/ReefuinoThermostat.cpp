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
static unsigned long DELAY = 60000L; //1min
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
	if (nextSwitchTime < millis()) {
		nextSwitchTime = millis() + DELAY;
		isWaitingForCooldown = false;
	} else {
		isWaitingForCooldown = true;
		status = COOLINGDOWN;
	}
	if (temp >= (_tempToKeep + actionBuffer)) {
		if (!isWaitingForCooldown) {
			_chillerRelay.turnOn();
			status = CHILLING;
		}
	}
	if (temp <= _tempToKeep) {
		if (!isWaitingForCooldown) {
			_chillerRelay.turnOff();
			status = RESTING;
		}
	}
	if (temp < (_tempToKeep - actionBuffer)) {
		if (!isWaitingForCooldown) {
			_heaterRelay.turnOn();
			status = HEATING;
		}
	}
	if (temp >= _tempToKeep) {
		if (!isWaitingForCooldown) {
			_heaterRelay.turnOff();
			status = RESTING;
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
//	return stringify( status );

//	string toString(Planet planet)
//	{
//	static string lookup[] = { "Mercury", "Venus", /*...*/, "Neptune" }
		return lookup[status];

//	char* result[];
//
//	const char* enMyErrorValueNames[] =
//	  {
//	  stringify( ERROR_INVALIDINPUT ),
//	  stringify( ERROR_NULLINPUT ),
//	  stringify( ERROR_INPUTTOOMUCH ),
//	  stringify( ERROR_IAMBUSY )
//	  };
//	switch (status) {
//	case (ThermostatStatus) HEATING:
//			result = "heating";
//		break;
//	case (ThermostatStatus) RESTING:
//			result = "resting";
//		break;
//	case (ThermostatStatus) CHILLING:
//			result = "chilling";
//		break;
//	case (ThermostatStatus) COOLINGDOWN:
//			result = "cooling down";
//		break;
//	}
//	return result;
}

void OnTimer(AlarmID_t Sender) {
// add code here to execute when the timer triggers
	Serial.println("timer triggered");
}

