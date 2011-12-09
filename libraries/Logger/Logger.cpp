#include "Logger.h"

Logger::Logger(int serialPort){
	Serial.begin(serialPort);

}

//<<destructor>>
Logger::~Logger(){/*nothing to destruct*/
}

void Logger::debug(String msg) {
	Serial.println("[DEBUG] " + msg);
}

void Logger::error(String msg){
	Serial.println("[ERROR] " + msg);
}





