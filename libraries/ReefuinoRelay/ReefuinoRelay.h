#ifndef ReefuinoRelay_H
#define ReefuinoRelay_H

#include <WProgram.h>

class ReefuinoRelay {
public:
  ReefuinoRelay(byte sensorPin);
  ~ReefuinoRelay();
  void on();
  void off();
  bool isOn();
  bool isOff();

private:
  int _sensorPin;
  boolean isActive;
};

#endif
