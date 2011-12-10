#include <math.h>
#include <TemperatureSensor.h>
#include <ReefuinoRelay.h>
#include <ReefuinoThermostat.h>
#include <Buzzer.h>
#include <Logger.h>
#include <ATO.h>
#include<stdlib.h>




#define Temp1Pin 0   // Analog Pin 
#define Temp2Pin 1   // Analog Pin 
#define RelayChillerPIN 9 
#define RelayHeaterPIN 8
#define BuzzerPin 11 

#define ATOPin 12 
#define ATOPumpPin 10

//Temperature control
double temperatureToKeep = 24.0;
TemperatureSensor waterTemperatureSensor(Temp1Pin);
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
}

void loop() {
  double temp = thermostat.checkTemperature(); 
  double standTemp = standTemperatureSensor.readCelsius();

  char msg[10] = "Temp: ";
  dtostrf(temp, 2, 2, msg);
  logger.debug(msg);

  if(thermostat.isHeating()){

  }

  if(thermostat.isHarmfulTemperature()){
    //    buzzer.bip();
  }
  delay(1000);                                      // Delay a bit... 
}






