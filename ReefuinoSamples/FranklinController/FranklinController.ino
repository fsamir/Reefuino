#include "ATO.h"
#include "Logger.h"
#include "ReefuinoRelay.h"
#include "OneWireTemperatureSensor.h"
//#include "ReefuinoThermostat.h"
#include <EtherCard.h>

#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)
#if STATIC
// ethernet interface ip address
static byte myip[] = { 
  192, 168, 1, 15 };
// gateway ip address
static byte gwip[] = { 
  192, 168, 1, 1 };
#endif
// ethernet mac address - must be unique on your network
static byte mymac[] = { 
  0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };


byte Ethernet::buffer[700];
static uint32_t timer;

char website[] PROGMEM = "www.google.com";



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

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  Serial.println("\n[webClient]");

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println( "Failed to access Ethernet controller");
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  

  if (!ether.dnsLookup(website))
    Serial.println("DNS failed");

  ether.printIp("SRV: ", ether.hisip);
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

  float temp2 = tempSensor.readCelsius(1);
  Logger::debug("Temperature for the device 2 is: ");
  Logger::debugFloat(temp2);

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

  ether.packetLoop(ether.packetReceive());

  if (millis() > timer) {
    timer = millis() + 5000;
    Serial.println();
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR("/foo/"), "bar", website, my_callback);
  }
}


// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
}




