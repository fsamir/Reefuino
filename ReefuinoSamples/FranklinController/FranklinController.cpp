#include "FranklinController.h"
#include "ATO.h"
#include "Logger.h"
#include "ReefuinoRelay.h"
#include "OneWireTemperatureSensor.h"
//#include "ReefuinoThermostat.h"

//ATO
const int ATOPin = 11;
const int ATOPumpPin = 9;
ReefuinoRelay atoPumpRelay(ATOPumpPin);
ATO ato(ATOPin, atoPumpRelay);

//Temperature
float temperatureToKeep = 26.0;
const int CHILLER_RELAY_PIN = 9; //digital

#define ONE_WIRE_PIN 4 //digital pin
#define TEMPERATURE_PRECISION 9
OneWireTemperatureSensor tempSensor(ONE_WIRE_PIN);
//ReefuinoRelay chillerRelay(CHILLER_RELAY_PIN);
//ReefuinoRelay heaterRelay(2);
//ReefuinoThermostat thermostat(tempSensor, chillerRelay, heaterRelay, temperatureToKeep);

void setup() {
	Logger::init(9600);
	Logger::debug("Listening Water level sensor on digital pin: " + ATOPin);
	tempSensor.init();
}

void loop() {
	//ATO
//	ato.checkSensorConnectivity();
	int atoValue = ato.onLoop();
	Logger::debug("ATO: " + String(atoValue));
	Logger::debug("is Topping: " + String(ato.isTopping()));

	//Temperature
	float temp = tempSensor.readCelsius();
	Logger::debug("Temperature for the device 1 is: ");
	Logger::debugFloat(temp);

	temp = tempSensor.readCelsius(1);
	Logger::debug("Temperature for the device 2 is: ");
	Logger::debugFloat(temp);

//	float temp = thermostat.checkTemperature();
//
//	Logger::debug("Celsius: ");
//	Logger::debugFloat(temp);
//
//	Logger::debug("Thermostat is: ");
//	Logger::debug(thermostat.getStatusStr());
////
//	if (thermostat.isHeating()) {
//		Logger::debug("Heater is on");
//	} else if (thermostat.isChilling()) {
//		Logger::debug("Fan is on");
//	} else {
//		Logger::debug("Temperature control is taking a nap");
//	}

	delay(1000);
}
