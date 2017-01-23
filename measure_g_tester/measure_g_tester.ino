#include <MsTimer2.h>

// Switch on LED on pin 13 each second


#define OPTO 6
#define SWITCH 7

volatile int c = 0;
volatile  boolean output = HIGH;

void flash() {
  c++;
  if (c % 2 == 1) {
    digitalWrite(SWITCH, HIGH); //switch to default
    for (int i = 0; i < 5; i++) {
      digitalWrite(OPTO, HIGH); //ballStarting
      delay(random(3,5));
      digitalWrite(OPTO, LOW);
      delay(random(3,5));
    }
  }
  else {
    for (int i = 0; i < 5; i++) {
      digitalWrite(SWITCH, LOW); //ballStarting
      delay(random(3,5));
      digitalWrite(SWITCH, HIGH);
      delay(random(3,5));
    }
    digitalWrite(SWITCH, LOW); //ballStop
    digitalWrite(OPTO, LOW); //opto to default
  }
   
  digitalWrite(13, output);
  output = !output;
}

void setup() {
  pinMode(OPTO, OUTPUT);
  pinMode(SWITCH, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(OPTO, LOW);
  digitalWrite(SWITCH, HIGH);
  MsTimer2::set(380, flash); // 500ms period
  MsTimer2::start();
}

void loop() {
}
