#include "Relay.h"
#undef double

Relay::Relay(int sensorPin) :_sensorPin(sensorPin) {
	pinMode(sensorPin, OUTPUT);
	isActive = false;
}

//<<destructor>>
Relay::~Relay() {/*nothing to destruct*/
}

void Relay::on() {
	digitalWrite(_sensorPin, HIGH);
	isActive = true;
}

void Relay::off() {
	digitalWrite(_sensorPin, LOW);
	isActive = false;
}

bool Relay::isOff() {
	return !isActive;
}

bool Relay::isOn() {
	return isActive;
}

