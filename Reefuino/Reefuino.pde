#include <math.h>
#define ThermistorPIN 0                 // Analog Pin 0

float vcc = 4.91;                       // only used for display purposes, if used
// set to the measured Vcc.
float pad = 9850;                       // balance/pad resistor value, set this to
// the measured resistance of your pad resistor
float thermr = 10000;                   // thermistor nominal resistance

int relayPin = 8;  
int value = 0; 
int HIGH_TEMP = 28;

float Thermistor(int RawADC) {
  long Resistance;  
  float Temp;  // Dual-Purpose variable to save space.

  Resistance=((1024 * pad / RawADC) - pad); 
  Temp = log(Resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius                      

  return Temp;                                      // Return the Temperature
}

void setup() {
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT); 
}

void loop() {
  float temp;
  temp=Thermistor(analogRead(ThermistorPIN));       // read ADC and  convert it to Celsius
  Serial.print(temp,1); 
  Serial.println(""); 

  if (temp > HIGH_TEMP) {  
    digitalWrite(relayPin, HIGH);  
  } 
  else {  
    digitalWrite(relayPin, LOW);     
  }  

  delay(500);                                      // Delay a bit... 
}

