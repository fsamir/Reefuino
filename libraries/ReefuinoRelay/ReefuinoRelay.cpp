#include "ReefuinoRelay.h" 
#undef double


ReefuinoRelay::ReefuinoRelay(byte sensorPin):_sensorPin(sensorPin) {
  pinMode(sensorPin, OUTPUT);
  isActive = false; 
}

//<<destructor>>
ReefuinoRelay::~ReefuinoRelay(){/*nothing to destruct*/
}

void ReefuinoRelay::on(){
  digitalWrite(_sensorPin, HIGH);     
  Serial.println("Relay " + String(_sensorPin) + " is on.");
  isActive = true;
}

void ReefuinoRelay::off(){
  digitalWrite(_sensorPin, LOW);
  Serial.println("Relay " + String(_sensorPin) + " is off.");    
  isActive = false;
}

bool ReefuinoRelay::isOff(){
	return !isActive;
}

bool ReefuinoRelay::isOn(){
	return isActive;
}



