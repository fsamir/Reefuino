#include "FranklinController.h"
#include "Logger.h"



void setup() {
	Logger::init(9600);
//	Serial.begin(9600);

	pinMode(1, OUTPUT);
}

void loop() {
//	Serial.println("frank");
	Logger::debug("logger");
	delay(1000);
}
