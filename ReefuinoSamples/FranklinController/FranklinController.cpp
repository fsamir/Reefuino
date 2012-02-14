#include "FranklinController.h"
#include "ATO.h"
#include "Logger.h"
#include "ATO.h"
#include "ReefuinoRelay.h"

const int ATOPin = 11;
const int ATOPumpPin = 9;

ReefuinoRelay atoPumpRelay(ATOPumpPin);
ATO ato(ATOPin, atoPumpRelay);

void setup() {
	Logger::init(9600);
	Logger::debug("Started listening Water level sensor on digital pin: " + ATOPin);
}

void loop() {
	ato.checkSensorConnectivity();

	int atoValue = ato.onLoop();
	Logger::debug("ATO: " + String(atoValue));

	Logger::debug("is Topping: " + String(ato.isTopping()));

	delay(1000);
}
