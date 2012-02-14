#include "ReefuinoRelay.h" 
#undef double

ReefuinoRelay::~ReefuinoRelay(){
}

void ReefuinoRelay::turnOn() {
	Relay::turnOn();
}

void ReefuinoRelay::turnOff() {
	Relay::turnOff();
}

bool ReefuinoRelay::isOff() {
	return Relay::isOff();
}

bool ReefuinoRelay::isOn() {
	return Relay::isOn();
}
