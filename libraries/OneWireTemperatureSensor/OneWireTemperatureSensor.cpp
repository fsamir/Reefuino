#include "OneWireTemperatureSensor.h"

OneWireTemperatureSensor::OneWireTemperatureSensor(int SensorPin) :
		oneWire(SensorPin), sensors(&oneWire) {
	_sensorPin = SensorPin;
}

OneWireTemperatureSensor::~OneWireTemperatureSensor() {
}

void OneWireTemperatureSensor::init() {
	// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
//	oneWire(_sensorPin);

// Pass our oneWire reference to Dallas Temperature.
//	sensors(&oneWire);

// arrays to hold device addresses
//	insideThermometer, outsideThermometer;

	sensors.begin();

	// locate devices on the bus
	Serial.print("Locating devices...");
	Serial.print("Found ");
	Serial.print(sensors.getDeviceCount(), DEC);
	Serial.println(" devices.");

	// report parasite power requirements
	Serial.print("Parasite power is: ");
	if (sensors.isParasitePowerMode())
		Serial.println("ON");
	else
		Serial.println("OFF");

}

float OneWireTemperatureSensor::readCelsius() {
	return readCelsius(0);
}

float OneWireTemperatureSensor::readCelsius(uint8_t deviceIndex) {
	sensors.requestTemperatures(); // Send the command to get temperatures

	float temp = sensors.getTempCByIndex(deviceIndex);
	return temp;
}
