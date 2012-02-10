#include "FranklinController.h"
//#include "ReefuinoRelay.h"

void setup() {
	Serial.begin(9600);

	pinMode(1, OUTPUT);
}

void loop() {
	Serial.println("frank");
	delay(100);
}
