#include "ATO.h"

//Schematics: http://www.arduino.cc/en/Tutorial/Button
/*
 (GND) --- (10k-Resistor) ----|---- (float switch) --- (+5v)
                              |
                           Analog Pin
 */
ATO::ATO(int pin, ReefuinoRelay relay) :
		atoPin(pin), pumpRelay(relay) {
	pinMode(atoPin, INPUT);
	Serial.println("Startd ATO on pin: " + atoPin);
}
//<<destructor>>
ATO::~ATO() {/*nothing to destruct*/
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

