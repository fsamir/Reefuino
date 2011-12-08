#include <math.h>
#include <TemperatureSensor.h>
#include <ReefuinoRelay.h>
#include <ReefuinoThermostat.h>
#include <Buzzer.h>



#define ThermistorPIN 0   // Analog Pin 0
#define RelayChillerPIN 8 
#define RelayHeaterPIN 9
#define BuzzerPin 11 

#define TempToKeep 24.0

 
double temperatureToKeep = 24.0;

TemperatureSensor temperatureSensor(ThermistorPIN);
ReefuinoRelay chillerRelay(RelayChillerPIN);
ReefuinoRelay heaterRelay(RelayHeaterPIN);
ReefuinoThermostat thermostat(temperatureSensor, chillerRelay, heaterRelay, temperatureToKeep);

Buzzer buzzer(BuzzerPin);

void setup() {
  Serial.begin(115200);  
  
 
}

void loop() {
  thermostat.checkTemperature(); 
//  buzzer.bip();
  
  if(thermostat.isHeating()){
    
  }
  delay(1000);                                      // Delay a bit... 
}


