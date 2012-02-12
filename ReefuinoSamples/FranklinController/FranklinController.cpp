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
	pinMode(1, OUTPUT);

}

void loop() {

	ato.checkSensorConnectivity();

	if (!ato.isOperatingProperly()) {
		Logger::alert("ATO sensor is not stable");
	}

	int atoValue = ato.onLoop();
	Logger::debug("ATO: " + String(atoValue));

	Logger::debug("is Topping: " + String(ato.isTopping()));

	delay(1000);
}
