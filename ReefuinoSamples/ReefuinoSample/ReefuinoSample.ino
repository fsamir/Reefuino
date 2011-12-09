#include <math.h>
#include <TemperatureSensor.h>
#include <ReefuinoRelay.h>
#include <ReefuinoThermostat.h>
#include <Buzzer.h>
#include <Logger.h>
#include<stdlib.h>




#define ThermistorPIN 0   // Analog Pin 0
#define RelayChillerPIN 9 
#define RelayHeaterPIN 8
#define BuzzerPin 11 

#define TempToKeep 24.0


double temperatureToKeep = 24.0;

TemperatureSensor temperatureSensor(ThermistorPIN);
ReefuinoRelay chillerRelay(RelayChillerPIN);
ReefuinoRelay heaterRelay(RelayHeaterPIN);
ReefuinoThermostat thermostat(temperatureSensor, chillerRelay, heaterRelay, temperatureToKeep);

Buzzer buzzer(BuzzerPin);
Logger logger(115200);

void setup() {

}

void loop() {
  double temp = thermostat.checkTemperature(); 

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


