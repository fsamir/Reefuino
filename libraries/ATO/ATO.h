#ifndef ATO_H
#define ATO_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "ReefuinoRelay.h"
#include "Logger.h"

class ATO {
public:
  ATO(int pin, ReefuinoRelay relay);
  ~ATO();
  bool onLoop();
  bool isTopping();

private:
  int atoPin;
  ReefuinoRelay pumpRelay;
};

#endif

