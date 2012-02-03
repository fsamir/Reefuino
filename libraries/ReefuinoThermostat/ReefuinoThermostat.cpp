#include "ReefuinoThermostat.h"
#include "TemperatureSensor.h"
#include "ReefuinoRelay.h"
//#include "Time.h"
//#include "TimeAlarms.h"

double actionBuffer = 0.5;
double harmfullFactor = 1.5;

bool isOn = false;
//Time to wait before taking an actions. Prevents frequent stops and starts due to short temperature fluctuations.
static unsigned long ACTIVATION_DELAY = 1000 * 60; //60 seconds

// Set a WARN status when the heater/chiller is operating for more than 2hs
static unsigned int DANGEROUS_OP_TIME_IN_SEC = 60 * 60 * 2; //2hs

unsigned long nextActivationTime = millis() + ACTIVATION_DELAY;
unsigned long lastActivationTime = 0;

bool shouldDelayingActivation = false;

//Chronodot clock;

//ReefuinoThermostat::ReefuinoThermostat(TemperatureSensor ts,
//		ReefuinoRelay chillerRelay, ReefuinoRelay heaterRelay,
//		double temperatureToKeep, Chronodot rtc) :
//		_tempToKeep(temperatureToKeep), _temperatureSensor(ts), _chillerRelay(
//				chillerRelay), _heaterRelay(heaterRelay), clock(clock) {
//	status = RESTING;
//}

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

	if (nextActivationTime > millis()) {
		Serial.println("delaying activation. \n");
		shouldDelayingActivation = true;
	} else {
		shouldDelayingActivation = false;
	}
	if (temp >= (_tempToKeep + actionBuffer)) {
		if (!shouldDelayingActivation && status != CHILLING
				&& status != CHILLING_WARN) {
			_chillerRelay.turnOn();
			_heaterRelay.turnOff();
			status = CHILLING;

			resetActivationDelay();
		} else {
			Serial.println("hot but waiting.");
		}
	} else if (temp < (_tempToKeep - actionBuffer)) {
		if (!shouldDelayingActivation && status != HEATING
				&& status != HEATING_WARN) {
			_heaterRelay.turnOn();
			_chillerRelay.turnOff();
			status = HEATING;

			resetActivationDelay();
		} else {
			Serial.println("cold but waiting.");
		}
	} else if (temp <= _tempToKeep || temp >= _tempToKeep) {
		if (!shouldDelayingActivation && status != RESTING) {
			_chillerRelay.turnOff();
			_heaterRelay.turnOff();
			status = RESTING;
			resetActivationDelay();
		} else {
			Serial.println("waiting to rest.");
		}
	}
	checkHarmfulOperationTime();
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
/**
 * Check whether the chiller or heater are working for a long time.
 * Can be used to prevent disasters due to broken equipment.
 */
void ReefuinoThermostat::checkHarmfulOperationTime() {
	if (status == HEATING && isWorkingTooLong()) {
		status = HEATING_WARN;
	} else if (status == CHILLING && isWorkingTooLong()) {
		status = CHILLING_WARN;
	}
}

bool ReefuinoThermostat::isWorkingTooLong() {
	return ((millis() - lastActivationTime) / 1000) > DANGEROUS_OP_TIME_IN_SEC;
}

bool ReefuinoThermostat::isHeating() {
	return _heaterRelay.isOn();
}

bool ReefuinoThermostat::isChilling() {
	return _chillerRelay.isOn();
}

ThermostatStatus ReefuinoThermostat::getStatus() {
	status;
}

String ReefuinoThermostat::getStatusStr() {
	return lookup[status];
}

void ReefuinoThermostat::resetActivationDelay() {
	Serial.println("XXX: resetting cooldown.");
	lastActivationTime = millis();
	nextActivationTime = (millis() + ACTIVATION_DELAY);
}

float ReefuinoThermostat::getTimeRemainingForNextActivation() {
	if (nextActivationTime > millis()) {
		return (nextActivationTime - millis()) / 1000;
	} else {
		return 0;
	}
}

/**
 * Last time the thermostat activated either chiller or heater.
 * In milliseconds
 */
long ReefuinoThermostat::getLastActivationTime() {
	return lastActivationTime;
}
