// Utilizes the Steinhart-Hart Thermistor Equation:
//    Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}
//    where A = 0.001129148, B = 0.000234125 and C = 8.76741E-08
#include <math.h>

double Thermister(int RawADC) {
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

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(double(Thermister(analogRead(0))));  // display Celsius
  delay(100);
}
