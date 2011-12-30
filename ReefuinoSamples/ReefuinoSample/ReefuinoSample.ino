#include <math.h>

#include <TemperatureSensor.h>
#include <ReefuinoRelay.h>
#include <Relay.h>
#include <ReefuinoThermostat.h>
#include <Buzzer.h>
#include <Logger.h>
#include <ATO.h>
#include<stdlib.h>

#include <Wire.h>
#include "Chronodot.h"
  
//class Chronodot;
//class DateTime;

#define WATER_TEMP_SENSOR_PIN 0   // Analog Pin 
#define STAND_TEMP_SENSOR_PIN 1   // Analog Pin 
#define RELAY_CHILLER_PIN 9 //digital
#define RELAY_HEATER_PIN 8 //digital
#define BUZZER_PIN 11 //digital

#define ATO_SENSOR_PIN 12 //digital
#define ATO_PUMP_PIN 10 //digital

//Water Temperature control
double temperatureToKeep = 26.0;
TemperatureSensor waterTemperatureSensor(WATER_TEMP_SENSOR_PIN);
ReefuinoRelay chillerRelay(RELAY_CHILLER_PIN);
ReefuinoRelay heaterRelay(RELAY_HEATER_PIN);

//Real time clock
Chronodot RTC;

ReefuinoThermostat thermostat(waterTemperatureSensor, chillerRelay, heaterRelay, temperatureToKeep, RTC);

//Stand temperature Sensor
TemperatureSensor standTemperatureSensor(STAND_TEMP_SENSOR_PIN);

//ATO
ReefuinoRelay atoPumpRelay(ATO_PUMP_PIN);
ATO ato(ATO_SENSOR_PIN, atoPumpRelay);

//Others
Buzzer buzzer(BUZZER_PIN);
Logger logger;

void setup() {
  Serial.begin(115200);
  //  logger.init(115200); //TODO: Investigate why this isn't working
  logger.debug("Reefuino Setup.");

  Serial.println("Initializing Chronodot.");
  Wire.begin();
  RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {
  DateTime now = RTC.now();
  
  float temp = thermostat.checkTemperature(); 
  float standTemp = standTemperatureSensor.readCelsius();

  Serial.print("Water: ");
  Serial.println(temp, 1);

  Serial.print("Stand: ");
  Serial.println(standTemp, 1);

//  logger.debug(msg);
//  logger.debug(standMsg);

  if(thermostat.isHeating()){

  }

  if(thermostat.isHarmfulTemperature()){
    buzzer.bip();
    if(temp > temperatureToKeep){
      logger.debug("High temperature alert.");
    } 
    else{
      logger.debug("Low temperature alert.");
    }
  }
  delay(3 * 1000); 
}









