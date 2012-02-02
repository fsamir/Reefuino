#include "ReefuinoRelay.h" 
#undef double

//<<destructor>>
ReefuinoRelay::~ReefuinoRelay(){/*nothing to destruct*/
}

void ReefuinoRelay::turnOn() {
	Relay::turnOn();
//	Serial.println("Relay " + String(_sensorPin) + " is on.");
}

void ReefuinoRelay::turnOff() {
	Relay::turnOff();
//	Serial.println("Relay " + String(_sensorPin) + " is off.");
}

bool ReefuinoRelay::isOff() {
	return Relay::isOff();
}

bool ReefuinoRelay::isOn() {
	return Relay::isOn();
}
