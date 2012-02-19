#include "NTCTemperatureSensor.h"

//Reference: http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1260958614
//http://medialappi.net/lab/equipment/sensors/environment-ntc-thermistor/
/*
 (Ground) ---- (Thermistor) -----|----- (10k-Resistor) ------ (+5v)
 |
 analog input
 */

//float vcc = 4.91; // only used for display purposes, if used set to the measured Vcc.
float pad = 9850; // balance/pad resistor value, set this to
// the measured resistance of your pad resistor
float thermr = 10000;

NTCTemperatureSensor::NTCTemperatureSensor(int SensorPin) {
	_sensorPin = SensorPin;
}

NTCTemperatureSensor::~NTCTemperatureSensor() {
}

double NTCTemperatureSensor::readCelsius() {
	return Thermister(analogRead(_sensorPin));
}

double NTCTemperatureSensor::thermister(int RawADC) {
	long Resistance;
	double Temp;

	Resistance = ((1024 * pad / RawADC) - pad);
	Temp = log(Resistance);

	// Assuming a 10k Thermistor.
	//Calculation is actually: Resistance = (1024 * BalanceResistor/ADC) - BalanceResistor
	Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
	Temp = Temp - 273.15; // Convert Kelvin to Celcius

	// Serial.print("ADC: ");
	// Serial.print(RawADC);
	//	Serial.print("/1024"); // Print out RAW ADC Number
	//	Serial.print(", vcc: ");
	//	Serial.print(vcc, 2);
	//	Serial.print(", pad: ");
	//	Serial.print(pad / 1000, 3);
	//	Serial.print(" Kohms, Volts: ");
	//	Serial.print(((RawADC * vcc) / 1024.0), 3);
	//	Serial.print(", Resistance: ");
	//	Serial.print(Resistance);
	//	Serial.print(" ohms, ");
	// END- Remove these lines for the function not to display anything
	//in case you need farenheit:
	// Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit

	return Temp;
}

