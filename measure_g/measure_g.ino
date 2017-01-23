/*
 Input Pullup Serial

 This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a
 digital input on pin 2 and prints the results to the serial monitor.

 The circuit:
 * Momentary switch attached from pin 2 to ground
 * Built-in LED on pin 13

 Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
 20K-ohm resistor is pulled to 5V. This configuration causes the input to
 read HIGH when the switch is open, and LOW when it is closed.

 created 14 March 2012
 by Scott Fitzgerald

 http://www.arduino.cc/en/Tutorial/InputPullupSerial

 This example code is in the public domain

 */

const float g_per_2 = 9.80665/2.0;

int printCounter = 0;

volatile unsigned long timer = 0;
volatile unsigned long elapsedTime = 0;

 void ballStarted() {
  timer = millis();
  elapsedTime = 0;
 }

 void ballStopped() {
  if (timer > 0) {
    elapsedTime = millis() - timer;
  }
  timer = 0;
 }

void setup() {
  //start serial connection
  Serial.begin(9600);
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(2, INPUT);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), ballStarted, RISING);
  attachInterrupt(digitalPinToInterrupt(2), ballStopped, FALLING);
  pinMode(13, OUTPUT);
  pinMode(A2, INPUT);
  digitalWrite(13, LOW);

}

void loop() {
  if (elapsedTime != 0) {
    printCounter++;
    Serial.print(printCounter);
    Serial.print(".   ");
    float et = (float)elapsedTime / 1000.0;
    Serial.print(et);
    Serial.print(" sec. s = ");
    float s = g_per_2 * et * et;
    Serial.print(s);
    Serial.print(" m, corr.s = ");
    Serial.println(s * 1.15 + 0.487);
    
    
    elapsedTime = 0;
  }
}



