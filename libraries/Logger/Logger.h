#ifndef Logger_H
#define Logger_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define LOG_ENABLED //Comment this out to disable logs.
class Logger {
public:
	static void debugFloat(float msg) {
		print("[DEBUG] ");
		printFloat(msg);
	}

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
	static void printFloat(float msg) {
#ifdef LOG_ENABLED
		Serial.println(msg,1);
#endif
	}
	static void println(String msg) {
#ifdef LOG_ENABLED
		Serial.println(msg);
#endif
	}
	static void print(String msg) {
#ifdef LOG_ENABLED
		Serial.print(msg);
#endif
	}
};

#endif

