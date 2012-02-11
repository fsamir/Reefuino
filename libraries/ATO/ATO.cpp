#include "ATO.h"

//Schematics: http://www.arduino.cc/en/Tutorial/Button
ATO::ATO(int pin, ReefuinoRelay relay) :
		atoPin(pin), pumpRelay(relay) {
	pinMode(atoPin, INPUT);
	Logger::debug("Started listening Water level sensor on digital pin: " + atoPin);
}

ATO::~ATO() {
}

bool ATO::onLoop() {
	int value = digitalRead(atoPin);
	if (value == HIGH) {
		pumpRelay.turnOn();
	} else {
		pumpRelay.turnOff();
	}

	return value;
}

bool ATO::isTopping() {
	return pumpRelay.isOn();
}

