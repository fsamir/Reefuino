#ifndef Logger_H
#define Logger_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "ReefuinoConfig.h"

class Logger {
public:
	static void debug(String msg) {
		println("[DEBUG] " + msg);
	}
	static void error(String msg) {
		println("[ERROR] " + msg);
	}
	static void init(int serialPort) {
		Serial.begin(serialPort);
		Serial.println("Started serial port: " + String(serialPort));
	}
	static void alert(String msg) {
		Serial.println("[WARNING] " + msg);
	}

private:
	static int serialPort;
	static void println(String msg) {
#ifdef LOG_ENABLED
		Serial.println( msg);
#endif
	}
};

#endif

