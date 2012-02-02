#include "Relay.h"
#undef double

Relay::Relay(int sensorPin) :_sensorPin(sensorPin) {
	pinMode(sensorPin, OUTPUT);
	isActive = false;
}

//<<destructor>>
Relay::~Relay() {/*nothing to destruct*/
}

void Relay::turnOn() {
	digitalWrite(_sensorPin, HIGH);
	isActive = true;
}

void Relay::turnOff() {
	digitalWrite(_sensorPin, LOW);
	isActive = false;
}

bool Relay::isOff() {
	return !isActive;
}

bool Relay::isOn() {
	return isActive;
}

