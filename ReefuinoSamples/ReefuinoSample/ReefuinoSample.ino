#include <math.h>
#include <TemperatureSensor.h>
#include <ReefuinoRelay.h>
#include <Relay.h>
#include <ReefuinoThermostat.h>
#include <Buzzer.h>
#include <Logger.h>
#include <ATO.h>
#include<stdlib.h>

#include "Chronodot.h"


#define WaterTemperatureSensorPin 0   // Analog Pin 
#define Temp2Pin 1   // Analog Pin 
#define RelayChillerPIN 9 //digital
#define RelayHeaterPIN 8 //digital
#define BuzzerPin 11 //digital

#define ATOPin 12 //digital
#define ATOPumpPin 10 //digital

//Water Temperature control
double temperatureToKeep = 26.0;
TemperatureSensor waterTemperatureSensor(WaterTemperatureSensorPin);
ReefuinoRelay chillerRelay(RelayChillerPIN);
ReefuinoRelay heaterRelay(RelayHeaterPIN);
ReefuinoThermostat thermostat(waterTemperatureSensor, chillerRelay, heaterRelay, temperatureToKeep);

//Stand temperature Sensor
TemperatureSensor standTemperatureSensor(Temp2Pin);

//ATO
ReefuinoRelay atoPumpRelay(ATOPumpPin);
ATO ato(ATOPin, atoPumpRelay);

//Others
Buzzer buzzer(BuzzerPin);
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
  double temp = thermostat.checkTemperature(); 
  double standTemp = standTemperatureSensor.readCelsius();

  char msg[12] = "Water: ";
  dtostrf(temp, 2, 2, msg);

  char standMsg[12] = "Stand: ";
  dtostrf(standTemp, 2, 2, standMsg);

  logger.debug(msg);
  logger.debug(standMsg);

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









