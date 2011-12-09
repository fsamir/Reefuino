#ifndef ReefuinoRelay_H
#define ReefuinoRelay_H
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class ReefuinoRelay {
public:
  ReefuinoRelay(int sensorPin);
  ~ReefuinoRelay();
  void on();
  void off();
  bool isOn();
  bool isOff();

private:
  int _sensorPin;
  bool isActive;
};

#endif
