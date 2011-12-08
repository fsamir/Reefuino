#ifndef Buzzer_H
#define Buzzer_H

#include <WProgram.h>

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

