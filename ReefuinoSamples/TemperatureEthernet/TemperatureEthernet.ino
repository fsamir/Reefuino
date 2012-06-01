#include "ATO.h"
#include "Logger.h"
#include "Relay.h"
#include "ReefuinoRelay.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "OneWireTemperatureSensor.h"
//#include "ReefuinoThermostat.h"
#include "EtherCard.h"

static byte mymac[] = { 
  0x74,0x69,0x69,0x2D,0x30,0x31 };
static byte myip[] = { 
  192,168,1,203 };

byte Ethernet::buffer[500];
BufferFiller bfill;

//ATO
const int ATOPin = 11;
const int ATOPumpPin = 9;
ReefuinoRelay atoPumpRelay(ATOPumpPin);
ATO ato(ATOPin, atoPumpRelay);

//Temperature
float temperatureToKeep = 26.0;
const int CHILLER_RELAY_PIN = 9; //digital

#define ONE_WIRE_PIN 4 //digital pin
#define TEMPERATURE_PRECISION 9
OneWireTemperatureSensor tempSensor(ONE_WIRE_PIN);
//ReefuinoRelay chillerRelay(CHILLER_RELAY_PIN);
//ReefuinoRelay heaterRelay(2);
//ReefuinoThermostat thermostat(tempSensor, chillerRelay, heaterRelay, temperatureToKeep);

void setup() {
  Logger::init(9600);
  Logger::debug("Listening Water level sensor on digital pin: " + ATOPin);
  tempSensor.init();

  setupEthernet();
}

void setupEthernet(){
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0){
    Serial.println( "Failed to access Ethernet controller");
  }
  ether.staticSetup(myip);
}

void loop() {
  //ATO
  //	ato.checkSensorConnectivity();
  int atoValue = ato.onLoop();
  Logger::debug("ATO: " + String(atoValue));
  Logger::debug("is Topping: " + String(ato.isTopping()));

  //Temperature
  float temp = tempSensor.readCelsius();
  Logger::debug("Temperature for the device 1 is: ");
  Logger::debugFloat(temp);

//  float temp2 = tempSensor.readCelsius(1);
//  Logger::debug("Temperature for the device 2 is: ");
//  Logger::debugFloat(temp2);

  //	float temp = thermostat.checkTemperature();
  //
  //	Logger::debug("Celsius: ");
  //	Logger::debugFloat(temp);
  //
  //	Logger::debug("Thermostat is: ");
  //	Logger::debug(thermostat.getStatusStr());
  ////
  //	if (thermostat.isHeating()) {
  //		Logger::debug("Heater is on");
  //	} else if (thermostat.isChilling()) {
  //		Logger::debug("Fan is on");
  //	} else {
  //		Logger::debug("Temperature control is taking a nap");
  //	}

  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  //
  //  if (pos)  {
  //    ether.httpServerReply(homePage()); // send web page data
  //  }
}
//
static word homePage() {
  long t = millis() / 1000;
  word h = t / 3600;
  byte m = (t / 60) % 60;
  byte s = t % 60;
  bfill = ether.tcpOffset();
  bfill.emit_p(PSTR(
  "HTTP/1.0 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Pragma: no-cache\r\n"
    "\r\n"
    "<meta http-equiv='refresh' content='1'/>"
    "<title>RBBB server</title>" 
    "<h1>$D$D:$D$D:$D$D</h1>"),
  h/10, h%10, m/10, m%10, s/10, s%10);
  return bfill.position();
}
//








