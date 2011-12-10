#include <ATO.h>
#include <Logger.h>
#include <ATO.h>
#include <ReefuinoRelay.h>

#define ATOPin 12 
#define ATOPumpPin 9 

Logger logger();
ReefuinoRelay atoPumpRelay(ATOPumpPin);
ATO ato(ATOPin, atoPumpRelay);

void setup() {
  Serial.begin(115200);
  //logger.init(115200);
}

void loop() {
  int value = ato.onLoop();
  Serial.println("ATO: "+String(value));
  
  Serial.println("is Topping: "+String(ato.isTopping()));
  

  delay(1000);
}





