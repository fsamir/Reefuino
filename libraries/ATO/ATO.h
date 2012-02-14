#ifndef ATO_H
#define ATO_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "ReefuinoRelay.h"

class ATO {
public:
  ATO(int pin, ReefuinoRelay relay);
  ~ATO();
  int onLoop();
  bool isTopping();
  bool isOperatingProperly();
  void checkSensorConnectivity();

private:
  int atoPin;
  ReefuinoRelay pumpRelay;
};

#endif

