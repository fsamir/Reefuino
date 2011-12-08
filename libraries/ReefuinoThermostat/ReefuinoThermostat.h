#ifndef ReefuinoThermostat_H
#define ReefuinoThermostat_H

#include <WProgram.h>
#include <ReefuinoRelay.h>
#include <TemperatureSensor.h>

class ReefuinoThermostat {
public:
  ReefuinoThermostat(TemperatureSensor ts, ReefuinoRelay chillerRelay, ReefuinoRelay heaterRelay, double temperatureToKeep);
  ~ReefuinoThermostat();
  double verify();
  bool isHeating();
  bool isChilling();

private:
  ReefuinoRelay _chillerRelay;
  ReefuinoRelay _heaterRelay;
  TemperatureSensor _temperatureSensor;
  double _tempToKeep;

};
#endif
