#include "ReefuinoRelay.h" 
#undef double

#include "Chronodot.h"

Chronodot RTC;

//<<destructor>>
ReefuinoRelay::~ReefuinoRelay(){/*nothing to destruct*/
}

void ReefuinoRelay::on() {
	Relay::on();
	Serial.println("Relay " + String(_sensorPin) + " is on.");
}

void ReefuinoRelay::off() {
	Relay::off();
	Serial.println("Relay " + String(_sensorPin) + " is off.");
}

bool ReefuinoRelay::isOff() {
	return Relay::isOff();
}

bool ReefuinoRelay::isOn() {
	return Relay::isOn();
}

