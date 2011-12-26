#include <math.h>
#define READING_PIN 1

double R1 = 10000.0; //resistance put in parallel
double V_IN = 5.0;

double A = 1.129148e-3;
double B = 2.34125e-4;
double C = 8.76741e-8;
double K = 9.5; // mW/dec C – dissipation factor

double SteinhartHart(double R)
{
  // calculate temperature
  double logR  = log(R);
  double logR3 = logR * logR * logR;

  return 1.0 / (A + B * logR + C * logR3 );

}

void setup() {
  Serial.begin(115200);
}

void loop() {
  double adc_raw = analogRead(READING_PIN);
  //Serial.println(adc_raw);
  double V =  adc_raw / 1024 * V_IN;
  Serial.print("V=");
  Serial.print(V);

  //calculate resistance
  double R_th = (R1 * V) / (V_IN - V);
  Serial.print("V R_th = ");
  Serial.print(R_th);

  double kelvin = SteinhartHart(R_th) - V*V/(K * R_th);
  double celsius = kelvin - 273.15;
  Serial.print("Ohm - T = ");
  Serial.print(celsius);
  Serial.print("C\n");
  delay(1000);
}






