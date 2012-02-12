#include "ATO.h"

bool isOk = true;
//Schematics: http://www.arduino.cc/en/Tutorial/Button
ATO::ATO(int pin, ReefuinoRelay relay) :
		atoPin(pin), pumpRelay(relay) {
	pinMode(atoPin, INPUT);
	Logger::debug(
			"Started listening Water level sensor on digital pin: " + atoPin);

	checkSensorConnectivity();
}

ATO::~ATO() {
}
/* Read the sensor 20 times and log an warning if the result is not always the same.*/
void ATO::checkSensorConnectivity() {
	int swapCounter = 0;
	int currentValue = 0;
	int previousValue = 0;
	for (int x = 0; x <= 20; x++) {
		currentValue = digitalRead(atoPin);
		if (previousValue != currentValue) {
			swapCounter++;
		}
		previousValue = currentValue;
	}

	if (swapCounter > 0) {
		isOk = false;
	}else{
		isOk = true;
	}
}

bool ATO::isOperatingProperly() {
	return isOk;
}

int ATO::onLoop() {
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

