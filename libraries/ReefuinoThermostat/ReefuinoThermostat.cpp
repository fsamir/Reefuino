#include "ReefuinoThermostat.h"
#include "TemperatureSensor.h"
#include "ReefuinoRelay.h"

double actionBuffer = 0.5;
double harmfullFactor = 1.5;

bool isOn = false;

//Simple timmer
//http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1233872134/all
//static unsigned long ACTIVATION_DELAY = 60000L; //1min
static unsigned long ACTIVATION_DELAY = 6000L; //6 seconds
unsigned long nextActivationTime = millis() + ACTIVATION_DELAY;
bool isDelayingActivation = false;


ReefuinoThermostat::ReefuinoThermostat(TemperatureSensor ts,
		ReefuinoRelay chillerRelay, ReefuinoRelay heaterRelay,
		double temperatureToKeep) :
		_tempToKeep(temperatureToKeep), _temperatureSensor(ts), _chillerRelay(
				chillerRelay), _heaterRelay(heaterRelay) {
	status = RESTING;
}

ReefuinoThermostat::~ReefuinoThermostat() {/*nothing to destruct*/
}

float ReefuinoThermostat::checkTemperature() {
	float temp = _temperatureSensor.readCelsius(); // read ADC and  convert it to Celsius
	//Check whether it should wait or the cooldown period has expired
	Serial.print("nextActivationTime: ");
	Serial.println(nextActivationTime);

	Serial.print("milis: ");
	Serial.println(millis());

	Serial.print("more ");
	long missingSeconds =  (nextActivationTime - millis()) /1000;
	Serial.print(missingSeconds);
	Serial.print("seconds to activate");

	if (nextActivationTime < millis()) {
		resetCooldown();
	} else {
		Serial.println("activating cooldown");
		isDelayingActivation = true;
		status = COOLINGDOWN;
	}
	if (temp >= (_tempToKeep + actionBuffer)) {
		if (!isDelayingActivation) {
			_chillerRelay.turnOn();
			status = CHILLING;
		}else{
			Serial.println("hot but waiting");
		}
	}
	if (temp <= _tempToKeep) {
		if (_chillerRelay.isOn() && !isDelayingActivation) {
			_chillerRelay.turnOff();
			status = RESTING;
		}else{
			Serial.println("not hot but waiting");
		}
	}
	if (temp < (_tempToKeep - actionBuffer)) {
		if (!isDelayingActivation) {
			_heaterRelay.turnOn();
			status = HEATING;
		}else{
			Serial.println("cold but waiting");
		}
	}
	if (temp >= _tempToKeep) {
		if (!isDelayingActivation) {
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
	if (temp >= _tempToKeep + harmfullFactor || temp <= _tempToKeep - harmfullFactor) {
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
	nextActivationTime = millis() + ACTIVATION_DELAY;
	isDelayingActivation = false;
}
