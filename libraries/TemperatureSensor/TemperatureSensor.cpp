#include "TemperatureSensor.h" 

//Reference: http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1260958614
/*
 (Ground) --- (10k-Resistor) ----|---- (Thermistor) --- (+5v)
 |
 Analog Pin ?
 */

#define ThermistorPIN 0                 // Analog Pin 0
float vcc = 4.91; // only used for display purposes, if used
// set to the measured Vcc.
float pad = 9850; // balance/pad resistor value, set this to
// the measured resistance of your pad resistor
float thermr = 10000; // thermistor nominal resistance

TemperatureSensor::TemperatureSensor(int SensorPin) {
	_sensorPin = SensorPin;
}

//<<destructor>>
TemperatureSensor::~TemperatureSensor() {/*nothing to destruct*/
}

double TemperatureSensor::readCelsius() {
	_compute(analogRead(_sensorPin));
}

float TemperatureSensor::_compute(int RawADC) {
	long Resistance;
	float Temp; // Dual-Purpose variable to save space.

	Resistance = ((1024 * pad / RawADC) - pad);
	Temp = log(Resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
	Temp = 1
			/ (0.001129148 + (0.000234125 * Temp)
					+ (0.0000000876741 * Temp * Temp * Temp));
	Temp = Temp - 273.15; // Convert Kelvin to Celsius

	// BEGIN- Remove these lines for the function not to display anything
	Serial.print("ADC: ");
	Serial.print(RawADC);
	Serial.print("/1024"); // Print out RAW ADC Number
	Serial.print(", vcc: ");
	Serial.print(vcc, 2);
	Serial.print(", pad: ");
	Serial.print(pad / 1000, 3);
	Serial.print(" Kohms, Volts: ");
	Serial.print(((RawADC * vcc) / 1024.0), 3);
	Serial.print(", Resistance: ");
	Serial.print(Resistance);
	Serial.print(" ohms, ");
	// END- Remove these lines for the function not to display anything

	// Uncomment this line for the function to return Fahrenheit instead.
	//temp = (Temp * 9.0)/ 5.0 + 32.0;                  // Convert to Fahrenheit
	return Temp;
}

