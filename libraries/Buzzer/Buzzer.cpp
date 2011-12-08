#include "Buzzer.h" 

int DefaultBuzzerPin = 9;
int length = 15; // the number of noteschar notes[] = "ccggaagffeeddc "; // a space represents a rest  
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };  
int tempo = 300;  
int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956   };
  
Buzzer::Buzzer(byte bp): buzzerPin(bp){
   pinMode(bp, OUTPUT); 
   Serial.println("Setting pin "+ String(bp) + " as a buzzer");
}
Buzzer::Buzzer(){
	buzzerPin = DefaultBuzzerPin;
   pinMode(DefaultBuzzerPin, OUTPUT); 
   Serial.println("Setting pin "+ String(DefaultBuzzerPin) + " as a buzzer");
}

//<<destructor>>
Buzzer::~Buzzer(){/*nothing to destruct*/
}

void Buzzer::bip() {
	Serial.println("Bip sensor:"+ String(buzzerPin));
	
	for (long i = 0; i < 512 ; i++ ) {
		digitalWrite(buzzerPin, HIGH);
		delayMicroseconds(44);
	    digitalWrite(buzzerPin, LOW);
		delayMicroseconds(44);
	}
	delay(1000);
}

void Buzzer::playMelody(){
	Serial.println("Melody on sensor:"+ String(buzzerPin));
   for (int i = 0; i < length; i++) {
    playNote(tones[i], beats[i] * tempo);
    delay(tempo / 2);
  }

}

void Buzzer::playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(tone);
  }
}

void Buzzer::playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'   };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}





