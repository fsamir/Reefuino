#include "OneWireTemperatureSensor.h"

//References
//http://bildr.org/2011/07/ds18b20-arduino/
//http://hackaday.com/2008/12/10/parts-1-wire-temperature-sensor-ds1822/

OneWireTemperatureSensor::OneWireTemperatureSensor(int SensorPin) :
		oneWire(SensorPin), sensors(&oneWire) {
	_sensorPin = SensorPin;
}

OneWireTemperatureSensor::~OneWireTemperatureSensor() {
}

void OneWireTemperatureSensor::init() {
	sensors.begin();

	// locate devices on the bus
	Logger::debug("Locating devices...");
	Logger::debug("Found " + String(sensors.getDeviceCount()) + " devices");

	//eport parasite power requirements
	Logger::debug("Parasite power is: ");
	if (sensors.isParasitePowerMode())
		Logger::debug("ON");
	else
		Logger::debug("OFF");

}

float OneWireTemperatureSensor::readCelsius() {
	return readCelsius(0);
}

float OneWireTemperatureSensor::readCelsius(uint8_t deviceIndex) {
	sensors.requestTemperatures(); // Send the command to get temperatures

	float temp = sensors.getTempCByIndex(deviceIndex);
	return temp;
}
