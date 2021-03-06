#include <math.h>
#include <Wire.h>
#include <Chronodot.h>
#include <TemperatureSensor.h>
#include <Relay.h>
#include <ReefuinoRelay.h>
#include <ReefuinoThermostat.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <Logger.h>



const int  TEMPERATURE_SENSOR_PIN = 0;   // Analog Pin 0
const int  FAN_RELAY_PIN = 9; //digital

double temperatureToKeep = 26.0;

TemperatureSensor temperatureSensor(TEMPERATURE_SENSOR_PIN);
ReefuinoRelay fanRelay(FAN_RELAY_PIN);
ReefuinoRelay heaterRelay(2);

ReefuinoThermostat thermostat(temperatureSensor, fanRelay, heaterRelay, temperatureToKeep);

void setup() {
  Serial.begin(115200);  

  Serial.print("Temperature is set to: ");   
  Serial.println(temperatureToKeep, DEC);   
}

void loop() {
  float temp = thermostat.checkTemperature(); 

  Serial.print("Celsius: "); 
  Serial.println(temp,1);

  //  thermostat.getStatus();

  Serial.print("Thermostat is: ");
  Serial.println(thermostat.getStatusStr()); 

  if(thermostat.isHeating()){
    Serial.println("Heater is on");    
  } 
  else if(thermostat.isChilling()){
    Serial.println("Fan is on");    
  } 
  else {
    Serial.println("Temperature control is taking a nap");    
  }
  delay(1000); 
}





