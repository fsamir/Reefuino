//#include <foo.h> inserts th file in this sketch
//#include "foo.h" Only references the classes in the file.
#include <math.h>
#include <TemperatureSensor.h>
#include <ReefuinoRelay.h>
#include <Relay.h>
#include <ReefuinoThermostat.h>
#include <ATO.h>
#include<stdlib.h>
#include "Logger.h"
#include "Time.h"
#include "TimeAlarms.h"

#include <Wire.h>
#include "Chronodot.h"


#define WATER_TEMP_SENSOR_PIN 0   // Analog Pin 
#define RELAY_CHILLER_PIN 9 //digital
#define RELAY_HEATER_PIN 8 //digital

#define ATO_SENSOR_PIN 12 //digital
#define ATO_PUMP_PIN 10 //digital

//Water Temperature control
double temperatureToKeep = 26.0;
TemperatureSensor waterTemperatureSensor(WATER_TEMP_SENSOR_PIN);
ReefuinoRelay chillerRelay(RELAY_CHILLER_PIN);
ReefuinoRelay heaterRelay(RELAY_HEATER_PIN);

ReefuinoThermostat thermostat(waterTemperatureSensor, chillerRelay, heaterRelay, temperatureToKeep);

//ATO
ReefuinoRelay atoPumpRelay(ATO_PUMP_PIN);
ATO ato(ATO_SENSOR_PIN, atoPumpRelay);

void setup() {
  //  Serial.begin(9600);
  Serial.begin(115200);
  //  logger.init(115200); //TODO: Investigate why this isn't working

  Serial.println("setup()");
}

void loop() {
  Serial.println("1.");
//  float temp = thermostat.checkTemperature(); 
    float temp = 1.2;
  Serial.println("2.");

  Serial.print("Water: ");
  Serial.println(temp, 1);

  Serial.println("3.");
  //  Serial.print("Thermostat is: ");
  //  Serial.println(thermostat.getStatusStr()); 



//  delay(1000); 
  Serial.println("4.");

}














