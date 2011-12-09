#ifndef Logger_H
#define Logger_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Logger {
public:
  Logger(int serialPort);
  ~Logger();
  void debug(String msg);
  void error(String msg);


private:

};

#endif

