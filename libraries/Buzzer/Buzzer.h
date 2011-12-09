#ifndef Buzzer_H
#define Buzzer_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Buzzer {
public:
  Buzzer(byte sensorPin);
  Buzzer();
  ~Buzzer();
  void bip();
  void playMelody();


private:
  unsigned int buzzerPin;
  void playTone(int tone, int duration);
  void playNote(char note, int duration);

};

#endif

