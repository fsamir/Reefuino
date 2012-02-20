#include "OneWireTempSensorSample.h"
#include "OneWireTemperatureSensor.h"

#define ONE_WIRE_PIN 4 //digital pin
#define TEMPERATURE_PRECISION 9

//References
//http://bildr.org/2011/07/ds18b20-arduino/
//http://hackaday.com/2008/12/10/parts-1-wire-temperature-sensor-ds1822/

OneWireTemperatureSensor tempSensor(ONE_WIRE_PIN);
void setup() {
//	Serial.begin(9600);
	Logger::init(9600);

	tempSensor.init();
}

void loop() {
	double temp = tempSensor.readCelsius();
	Logger::debug("Temperature for the device 1 (index 0) is: ");
	Logger::debugFloat(temp);

	temp = tempSensor.readCelsius(1);
	Logger::debug("Temperature for the device 2 (index 1) is: ");
	Logger::debugFloat(temp);

}
