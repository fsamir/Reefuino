#include <ATO.h>
#include <Relay.h>
#include <ReefuinoRelay.h>

#define WATER_LVL_SENSOR_PIN 12 
#define ATO_PUMP_RELAY_PIN 10

ReefuinoRelay atoPumpRelay(ATO_PUMP_RELAY_PIN);
ATO ato(WATER_LVL_SENSOR_PIN, atoPumpRelay);

void setup() {
  Serial.begin(115200);
}

void loop() {
  int value = ato.onLoop();
  Serial.println("ATO: "+String(value));
  
  Serial.println("is Topping: "+String(ato.isTopping()));
  

  delay(1000);
}





