#ifndef ReefuinoRelay_H
#define ReefuinoRelay_H
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Relay.h>

class ReefuinoRelay : public Relay {
public:
  ReefuinoRelay(int sensorPin): Relay(sensorPin){ }
  ~ReefuinoRelay();
  void turnOn();
  void turnOff();
  bool isOn();
  bool isOff();

private:

};

#endif
