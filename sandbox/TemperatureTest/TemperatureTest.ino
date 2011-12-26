#include <math.h>


http://www.arduino.cc/playground/ComponentLib/Thermistor2

// enumarating 3 major temperature scales
enum {
  T_KELVIN=0,
  T_CELSIUS,
  T_FAHRENHEIT
};

// manufacturer data for episco k164 10k thermistor
// simply delete this if you don't need it
// or use this idea to define your own thermistors
#define EPISCO_K164_10k 4300.0f,298.15f,10000.0f  // B,T0,R0

// Temperature function outputs float , the actual 
// temperature
// Temperature function inputs
// 1.AnalogInputNumber - analog input to read from 
// 2.OuputUnit - output in celsius, kelvin or fahrenheit
// 3.Thermistor B parameter - found in datasheet 
// 4.Manufacturer T0 parameter - found in datasheet (kelvin)
// 5. Manufacturer R0 parameter - found in datasheet (ohms)
// 6. Your balance resistor resistance in ohms  

float Temperature(int AnalogInputNumber,int OutputUnit,float B,float T0,float R0,float R_Balance){
  float R,T;

  R=1024.0f*R_Balance/float(analogRead(AnalogInputNumber))-R_Balance;
  T=1.0f/(1.0f/T0+(1.0f/B)*log(R/R0));

  switch(OutputUnit) {
  case T_CELSIUS :
    T-=273.15f;
    break;
  case T_FAHRENHEIT :
    T=9.0f*(T-273.15f)/5.0f+32.0f;
    break;
  default:
    break;
  };

  return T;
}
void setup() {
  Serial.begin(115200);
}


// example of use #1
// reading from analog input 1, using episco k164 definition
// and 10k balance, getting result in celsius
void loop() {

  Serial.println("*************************");
  Serial.println("A: 10k Balance");
  Serial.println(Temperature(0,T_CELSIUS,EPISCO_K164_10k,10000.0f));
//  Serial.println("B: 10k Balance");
//  Serial.println(Temperature(1,T_CELSIUS,4300.0f,298.15f,10000.0f,10000.0f));


  delay(2 * 1000);
}

//example of use #2
// using numbers instead of episco k164 definition
// this time reading from analog input 2
// getting result in fahrenheit

//
//void loop() {
//
//  Serial.println("*************************");
//  Serial.println("10k Balance");
//  Serial.println(Temperature(2,T_FAHRENHEIT,4300.0f,298.15f,10000.0f,10000.0f));
//  Serial.println("*************************");
//
//  delay(500);
//}

