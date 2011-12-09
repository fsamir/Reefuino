#include <math.h>
#include <ATO.h>
#include <Logger.h>
#include<stdlib.h>

#define HighPin 2   // Analog Pin 0
#define LowPin 3 

Logger logger(115200);

void setup() {
}

void loop() {
  int low = digitalRead(LowPin);
  logger.debug("Low: "+ low);
  int high = digitalRead(HighPin);
  delay(1000);                                      // Delay a bit... 
}



