#include "TemperatureSensor.h" 

//Reference: http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1260958614
/*
 (Ground) --- (10k-Resistor) ----|---- (Thermistor) --- (+5v)
                                 |
                            Analog Pin ?
*/

// manufacturer data for episco k164 10k thermistor
// simply delete this if you don't need it
// or use this idea to define your own thermistors
#define EPISCO_K164_10k 4300.0f,298.15f,10000.0f  // B,T0,R0

TemperatureSensor::TemperatureSensor(int SensorPin){
  _sensorPin = SensorPin;
}

//<<destructor>>
TemperatureSensor::~TemperatureSensor(){/*nothing to destruct*/
}

double TemperatureSensor::readCelsius(){
  _compute(analogRead(_sensorPin));
}

float TemperatureSensor::_compute(int RawADC) {
  double Temp;

  Temp = log(((10240000/RawADC) - 10000));
  // Assuming a 10k Thermistor.
  //Calculation is actually: Resistance = (1024 * BalanceResistor/ADC) - BalanceResistor

  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius

  //in case you need farenheit:
  // Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit

  return Temp;
}


