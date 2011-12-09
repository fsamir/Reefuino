#ifndef ATO_H
#define ATO_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class ATO {
public:
  ATO(int highPin, int lowPin);
  ~ATO();
  bool isActive();

private:
  int lowPin;
  int highPin;
};

#endif

