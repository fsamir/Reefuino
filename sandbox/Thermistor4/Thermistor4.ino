// Thermister4 Library version 4c. For Arduino 0018 or newer.
// (c)20101017 by MODAT7 under GNU GPLv1

//Example code of various functions using my 2 salvaged thermistors.

#include "Thermistor4.h"

//Faster serial means shorter delays in the program.
#define SERIALBAUD 115200

//Inside thermistor on Arduino ADC pin 0, Outside on pin 1.
#define THERMISTORPinInside 0
#define THERMISTORPinOutside 1

//========================================

//One temperature monitoring thermistor for Inside and Outside.
Thermistor4 ThermistorInside, ThermistorOutside;
//various temp variables for testing.
unsigned int i, ADCAverage;
double mytemp;
unsigned long mytime1, mytime2; //for speed tests


//========================================
void setup() {

  //pin floating paranoia, set pullup's (don't mess with 0 and 1 serial).
  for(int i=2; i<20; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }

  Serial.begin(SERIALBAUD); //set up serial port.

  //My 2 salvaged thermistors are about 30k at room temperature.
  ThermistorInside.Pin = THERMISTORPinInside; //Set the pin number.
  ThermistorOutside.Pin = THERMISTORPinOutside;
  ThermistorInside.SetUp(); //Sets up the analog read pin for internal AVR.
  ThermistorOutside.SetUp(); //If using an external ADC, write your own setup here.
  //pow() is used elsewhere so might as well be used here.
  ThermistorInside.BitResolution=pow(2, 10)-1; //ATmega's have a 10bit ADC (2^10-1).
  ThermistorOutside.BitResolution=pow(2, 10)-1; //An external ADC may be lower or higher than 10bits.
  ThermistorInside.VoltageSupply=4.95; //My USB powers my ATmega325 chip at 4.95v. Meter this for accuracy.
  ThermistorOutside.VoltageSupply=4.95; //An external ADC may have different voltages. Meter this for accuracy.
  ThermistorInside.ResistanceFixed=27200; //Fixed resistor in the divider. Measured in ohms. Meter this for accuracy.
  ThermistorOutside.ResistanceFixed=27100; //The resistor divider should be calculated to maximize desired range.
  ThermistorInside.Offset=0.4; //adjust temperature in Kelvin up or down a little to account for unforseen variations.
  ThermistorOutside.Offset=0.4; //This will be by trial and error during final manual calibration.
  //These numbers were generated from thermistor.sf.net and aren't quite right unless using the full equation.
  ThermistorInside.SteinhartA1=1.560442157476244e-003;  //First Steinhart-Hart coefficient.
  ThermistorInside.SteinhartA2=-1.298742723052728e-005; //Second Steinhart-Hart coefficient.
  ThermistorInside.SteinhartA3=2.500508035979886e-005;  //Third Steinhart-Hart coefficient.
  ThermistorInside.SteinhartA4=-7.698170259653937e-007; //Fourth Steinhart-Hart coefficient.
  ThermistorOutside.SteinhartA1=2.975623989921602e-003;  //First Steinhart-Hart coefficient.
  ThermistorOutside.SteinhartA2=-4.448067018378571e-004; //Second Steinhart-Hart coefficient.
  ThermistorOutside.SteinhartA3=6.848365975770642e-005;  //Third Steinhart-Hart coefficient.
  ThermistorOutside.SteinhartA4=-2.217688558250577e-006; //Fourth Steinhart-Hart coefficient.

} //end setup()


//========================================
void loop() {

#if THERMISTORDEBUG
  //Show the debugging information:
  Serial.println("");
  Serial.println("ThermistorInside Debug: ");
  ThermistorInside.Thermistor4SerialPrint();
  Serial.println("");
  Serial.println("ThermistorOutside Debug: ");
  ThermistorOutside.Thermistor4SerialPrint();
  Serial.println("");
#endif

  //Nice printout form.
  ThermistorInside.ReadCalculate(3);
  Serial.print("Inside Temp (F): "); 
  Serial.println(ThermistorInside.GetFarenheit(), 2);
  ThermistorOutside.ReadCalculate(3);
  Serial.print("Outside Temp (F): "); 
  Serial.println(ThermistorOutside.GetFarenheit(), 2);

  //Example CSV output that can be extracted from the other information and plotted.
  //unix/linux: grep "^CSV," > outfile.csv
  ThermistorInside.ReadCalculate(3);
  Serial.print("CSV,"); 
  Serial.print(ThermistorInside.GetFarenheit(), 2);
  Serial.print(","); 
  Serial.print(ThermistorInside.GetCentigrade(), 2);
  ThermistorOutside.ReadCalculate(3);
  Serial.print(","); 
  Serial.print(ThermistorOutside.GetFarenheit(), 2);
  Serial.print(","); 
  Serial.println(ThermistorOutside.GetCentigrade(), 2);

  //Example of averaging 10 reads. Note that analogRead() isn't very fast.
  //Part of this code has to be done manually, then call ReadADC() with the averaged number.
  //Note that an unsigned int is only 16 bits. Do not exceed it or it will roll over and return trash.
  ADCAverage = 0; //reset the variable for each loop.
  for(i=0; i<10; i++) {
    ADCAverage += analogRead(THERMISTORPinInside);
    //delay(50); //add an extra delay to spread the average out a little more?
  }
  ThermistorInside.ReadADC(ADCAverage/10); //call ReadADC() with the averaged value.
  ThermistorInside.CalculateTemperature(3); //generate the temperature numbers.
  //Report as normal from here on out.
  Serial.print("ThermistorInside Averaged (Centigrade, Farenheit): ");
  Serial.print(ThermistorInside.GetCentigrade(), 2);
  Serial.print(", ");
  Serial.println(ThermistorInside.GetFarenheit(), 2);

  //Note: ReadCalculate() doesn't have to be called this much per loop, but it is shown for clarity.

  //Timing how long some code runs...
  //This could be done inside the class, but timings would be off.
  Serial.println("Doing timing loop test...");
  mytime1=millis(); //save the start time
  for(i=0; i<1000; i++) {
    ThermistorInside.ReadCalculate(1);
    mytemp=ThermistorInside.GetFarenheit();
  }
  mytime2 = millis() - mytime1;
  Serial.print("1000 Farehneit reads in milliseconds (ReadCalculate(1)): ");
  Serial.println(mytime2); //print out time

  //Timing how long some code runs...
  //This could be done inside the class, but timings would be off.
  Serial.println("Doing timing loop test...");
  mytime1=millis(); //save the start time
  for(i=0; i<1000; i++) {
    ThermistorInside.ReadCalculate(2);
    mytemp=ThermistorInside.GetFarenheit();
  }
  mytime2 = millis() - mytime1;
  Serial.print("1000 Farehneit reads in milliseconds (ReadCalculate(2)): ");
  Serial.println(mytime2); //print out time

  //Timing how long some code runs...
  //This could be done inside the class, but timings would be off.
  Serial.println("Doing timing loop test...");
  mytime1=millis(); //save the start time
  for(i=0; i<1000; i++) {
    ThermistorInside.ReadCalculate(3);
    mytemp=ThermistorInside.GetFarenheit();
  }
  mytime2 = millis() - mytime1;
  Serial.print("1000 Farehneit reads in milliseconds (ReadCalculate(3)): ");
  Serial.println(mytime2); //print out time

  //Wait 10 seconds to avoid screen flooding.
  delay(10000);

} //end loop()

//end of Thermistor4c.pde

