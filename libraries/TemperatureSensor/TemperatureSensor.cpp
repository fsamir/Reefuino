#include "TemperatureSensor.h" 


TemperatureSensor::TemperatureSensor(byte SensorPin){
  _SensorPin = SensorPin;
}

//<<destructor>>
TemperatureSensor::~TemperatureSensor(){/*nothing to destruct*/
}

//turn the LED on
double TemperatureSensor::ReadCelsius(){
  _Compute(analogRead(_SensorPin));
}


double TemperatureSensor::_Compute(int RawADC) {
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


