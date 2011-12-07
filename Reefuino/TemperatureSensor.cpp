#include "TemperatureSensor.h" //include the declaration for this class

const byte LED_PIN = 13; //use the LED @ Arduino pin 13, this should not change so make it const (constant)

TemperatureSensor::TemperatureSensor(int pin){
  pinMode(LED_PIN, OUTPUT); //make that pin an OUTPUT
}

//<<destructor>>
TemperatureSensor::~TemperatureSensor(){/*nothing to destruct*/
}

//turn the LED on
void TemperatureSensor::Read(){
  digitalWrite(13,HIGH); //set the pin HIGH and thus turn LED on
}

//turn the LED off
void TemperatureSensor::off(){
  digitalWrite(LED_PIN,LOW); //set the pin LOW and thus turn LED off
}

//blink the LED in a period equal to paramterer -time.
//void LED13::blink(int time){
//  on();                   //turn LED on
//  delay(time/2);  //wait half of the wanted period
//  off();                  //turn LED off
//  delay(time/2);  //wait the last half of the wanted period
//}



