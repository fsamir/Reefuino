#include "ReefuinoThermostat.h"
#include "TemperatureSensor.h"
#include "ReefuinoRelay.h"


double actionBuffer = 0.5;
double harmfullFactor = 1.5;

bool isOn = false;

ReefuinoThermostat::ReefuinoThermostat(TemperatureSensor ts, ReefuinoRelay chillerRelay, ReefuinoRelay heaterRelay, double temperatureToKeep)
 :_tempToKeep(temperatureToKeep), _temperatureSensor(ts), _chillerRelay(chillerRelay), _heaterRelay(heaterRelay) {
}

//<<destructor>>
ReefuinoThermostat::~ReefuinoThermostat(){/*nothing to destruct*/
}

float ReefuinoThermostat::checkTemperature(){
  float temp = _temperatureSensor.readCelsius();       // read ADC and  convert it to Celsius
  if(temp >= (_tempToKeep + actionBuffer)){
        _chillerRelay.on();
  }
  if(temp <= _tempToKeep) {
    	_chillerRelay.off();		
  }
  if(temp < (_tempToKeep - actionBuffer)) {
    	_heaterRelay.on();
  }
  if(temp >= _tempToKeep){
    	_heaterRelay.off();
  }
  return temp;
}

/*Is the temperature dangerously high or low? */
bool ReefuinoThermostat::isHarmfulTemperature() {
	double temp = _temperatureSensor.readCelsius();
	if(temp >= _tempToKeep + harmfullFactor	|| temp <= _tempToKeep - harmfullFactor){
		return true;
	}else{
		return false;
	}
}

bool ReefuinoThermostat::isHeating() {
	return _heaterRelay.isOn();
}

bool ReefuinoThermostat::isChilling() {
	return _chillerRelay.isOn();
}




