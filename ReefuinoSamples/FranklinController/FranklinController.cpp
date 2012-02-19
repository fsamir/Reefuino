#include "FranklinController.h"
#include "ATO.h"
#include "Logger.h"
//#include "ReefuinoRelay.h"
//#include "TemperatureSensor.h"
//#include "ReefuinoThermostat.h"

//ATO
const int ATOPin = 11;
const int ATOPumpPin = 9;
ReefuinoRelay atoPumpRelay(ATOPumpPin);
ATO ato(ATOPin, atoPumpRelay);

//Temperature
//double temperatureToKeep = 26.0;
//const int TEMPERATURE_SENSOR_PIN = 0; // Analog Pin 0
//const int CHILLER_RELAY_PIN = 9; //digital
//TemperatureSensor temperatureSensor(TEMPERATURE_SENSOR_PIN);
//ReefuinoRelay chillerRelay(CHILLER_RELAY_PIN);
//ReefuinoRelay heaterRelay(2);
//ReefuinoThermostat thermostat(temperatureSensor, chillerRelay, heaterRelay,
//		temperatureToKeep);

void setup() {
	Logger::init(9600);
	Logger::debug("Listening Water level sensor on digital pin: " + ATOPin);
}

void loop() {
	//ATO
	ato.checkSensorConnectivity();
	int atoValue = ato.onLoop();
	Logger::debug("ATO: " + String(atoValue));
	Logger::debug("is Topping: " + String(ato.isTopping()));

	//Temperature
//	float temp = thermostat.checkTemperature();

//	Logger::debug("Celsius: ");
//	Logger::debugFloat(temp);

//	Logger::debug("Thermostat is: ");
//	Logger::debug(thermostat.getStatusStr());
//
//	if (thermostat.isHeating()) {
//		Logger::debug("Heater is on");
//	} else if (thermostat.isChilling()) {
//		Logger::debug("Fan is on");
//	} else {
//		Logger::debug("Temperature control is taking a nap");
//	}

	delay(1000);
}
