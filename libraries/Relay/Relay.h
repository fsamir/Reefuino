#ifndef Relay_H
#define Relay_H
//#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
//#else
//#include "WProgram.h"
//#endif

class Relay {
public:
	Relay(int sensorPin);
	~Relay();
	virtual void turnOn();
	virtual void turnOff();
	virtual bool isOn();
	virtual bool isOff();

private:

protected:
	int _sensorPin;
	bool isActive;
};

#endif
