#include "Logger.h"

Logger::Logger(){

}

//<<destructor>>
Logger::~Logger(){/*nothing to destruct*/
}

void Logger::init(int serialPort) {
	Serial.begin(serialPort);
	Serial.println("Started serial port: "+String(serialPort));
}

void Logger::debug(String msg) {
	Serial.println("[DEBUG] " + msg);
}

void Logger::error(String msg){
	Serial.println("[ERROR] " + msg);
}





