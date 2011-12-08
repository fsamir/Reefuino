#include "ReefuinoThermostat.h"
#include "TemperatureSensor.h"
#include "ReefuinoRelay.h"


double tempFactor = 0.5;

bool isOn = false;

ReefuinoThermostat::ReefuinoThermostat(TemperatureSensor ts, ReefuinoRelay chillerRelay, ReefuinoRelay heaterRelay, double temperatureToKeep)
 :_tempToKeep(temperatureToKeep), _temperatureSensor(ts), _chillerRelay(chillerRelay), _heaterRelay(heaterRelay) {
}

//<<destructor>>
ReefuinoThermostat::~ReefuinoThermostat(){/*nothing to destruct*/
}


double ReefuinoThermostat::checkTemperature(){
  double temp = _temperatureSensor.ReadCelsius();       // read ADC and  convert it to Celsius

  if(temp >= (_tempToKeep + tempFactor)){
        _chillerRelay.on();
  }
  if(temp <= _tempToKeep) {
    	_chillerRelay.off();		
  }
  if(temp < (_tempToKeep - tempFactor)) {
    	_heaterRelay.on();
  }
  if(temp >= _tempToKeep){
    	_heaterRelay.off();
  }

  return temp;
}

bool ReefuinoThermostat::isHeating() {
	return _heaterRelay.isOn();
}

bool ReefuinoThermostat::isChilling() {
	return _chillerRelay.isOn();
}




