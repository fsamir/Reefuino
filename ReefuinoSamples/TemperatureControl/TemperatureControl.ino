#include <math.h>
#include <Wire.h>
#include <Chronodot.h>
#include <TemperatureSensor.h>
#include <Relay.h>
#include <ReefuinoRelay.h>
#include <ReefuinoThermostat.h>

#include "Time.h"
#include "TimeAlarms.h"
#include "Logger.h"

#define ThermistorPIN 0   // Analog Pin 0
#define RelayChillerPIN 9 
#define RelayHeaterPIN 8

double temperatureToKeep = 26.0;

TemperatureSensor secondary(1);

TemperatureSensor temperatureSensor(ThermistorPIN);
ReefuinoRelay chillerRelay(RelayChillerPIN);
ReefuinoRelay heaterRelay(RelayHeaterPIN);
ReefuinoThermostat thermostat(temperatureSensor, chillerRelay, heaterRelay, temperatureToKeep);

void setup() {
  Serial.begin(115200);  
  
  Serial.print("Temperature is set to: ");   
    Serial.println(temperatureToKeep, DEC);   
}

void loop() {
  float temp = thermostat.checkTemperature(); 
  Serial.print("Celsius: "); 
  Serial.println(temp,1);

  float temp2 = secondary.readCelsius();
   Serial.println("");
  Serial.print("temp 2: "); 
  Serial.println(temp2,1);

  
//  if(thermostat.isHeating()){
//    Serial.println("Heater is on");    
//  } else if(thermostat.isChilling()){
//    Serial.println("Chiller is on");    
//  } else {
//    Serial.println("Temperature control is taking a nap");    
//  }
  delay(1000 * 5); 
}


