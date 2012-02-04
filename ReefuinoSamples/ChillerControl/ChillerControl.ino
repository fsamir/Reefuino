#include <math.h>

#include <TemperatureSensor.h>
#include <Relay.h>
#include <ReefuinoRelay.h>
#include <ReefuinoThermostat.h>
//#include <Wire.h>
//#include <Chronodot.h>
//#include <Time.h>
//#include <TimeAlarms.h>
//#include <Logger.h>

#define TEMPERATURE_SENSOR_PIN 0   // Analog Pin 0
#define CHILLER_RELAY_PIN 9 //digital

double temperatureToKeep = 26.0;

TemperatureSensor temperatureSensor(TEMPERATURE_SENSOR_PIN);
ReefuinoRelay chillerRelay(CHILLER_RELAY_PIN);
ReefuinoRelay heaterRelay(2);

ReefuinoThermostat thermostat(temperatureSensor, chillerRelay, heaterRelay, temperatureToKeep);

void setup() {

  Serial.begin(115200);  

  //  Serial.print("Temperature is set to: ");   
  //  Serial.println(temperatureToKeep, DEC);   
  Serial.print("setup"); 
}

void loop() {
  float temp = thermostat.checkTemperature(); 

  Serial.print("Celsius: "); 
  Serial.println(temp,1);

  Serial.print("Status: ");
  Serial.println(""+ thermostat.getStatusStr()); 
  //Serial.println(thermostat.getStatus()); 

  float next = thermostat.getSecondsRemainingForNextActivation();
  Serial.print("\nDelay until next activation: ");
  //  Serial.print((next - millis() )/1000, 1);
  Serial.print(next, 1);
  Serial.println(""); 

  Serial.print("Last action: ");
  long last = thermostat.getLastActivationTime();
  Serial.print((millis() - last)/1000, 1);
  Serial.println(" secs ago.");


  Serial.println(""); 
  delay(1000 * 2); 
}











