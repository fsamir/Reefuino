#ifndef Logger_H
#define Logger_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Logger {
public:
  Logger();
  ~Logger();
  static void debug(String msg);
  void error(String msg);
  void init(int serialPort);

private:
  int serialPort;
};

#endif

