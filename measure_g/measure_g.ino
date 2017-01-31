#define VERSION "1.1"

// Both pins are normally HIGH
// START_PIN goes LOW when ball goes through between the IR LED and the phototransistor
#define START_PIN 3
// STOP_PIN goes LOW when ball hits the ground (and pushes one of the buttons)
#define STOP_PIN 2

const float g_per_2 = 9.80665/2.0;

int printCounter = 0;

unsigned long timer = 0;      // millis when ball start to fall down
unsigned long elapsedTime = 0;// millis between ball start and stop
unsigned long tmp = 0;

volatile boolean isBallStarted = false;
volatile boolean isBallStopped = false;

volatile int stopCounter = 0;
volatile int startCounter = 0;

 void ballStarted() {
  startCounter++;
  isBallStarted = true;
  digitalWrite(13, HIGH);
 }

 void ballStopped() {
  stopCounter++;
  isBallStopped = true;
  digitalWrite(13, LOW);
 }

void setup() {
  Serial.begin(9600);
  pinMode(START_PIN, INPUT);
  pinMode(STOP_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(START_PIN), ballStarted, FALLING);
  attachInterrupt(digitalPinToInterrupt(STOP_PIN),  ballStopped, FALLING);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.print("Freefall-time stopper, version:");
  Serial.println(VERSION);
  Serial.println("Peter Borkuti");
}

void printData() {
    printCounter++;

    Serial.print(printCounter);
    Serial.print("|   ");
    Serial.print(startCounter);
    Serial.print(",");
    Serial.print(stopCounter);
    Serial.print("|   ");
    //elapsed time in millis, print it in seconds
    float et = (float)elapsedTime / 1000.0;
    Serial.print(et);
    Serial.print(" sec. s = ");
    // the length of free fall is g/2*t^2
    float s = g_per_2 * et * et;
    Serial.println(s);
}

void loop() {
  if (isBallStarted && (timer == 0)) {
    timer = millis();
  }
  
  if (isBallStopped) {
    tmp = millis() - timer;
    //bouncing
    delay(500);

    if (isBallStarted) {
      elapsedTime = tmp;
      printData();
    }

    //if user just pushes the switches, dont measure
    isBallStopped = false;
    isBallStarted = false;
    timer = 0;
  }
}

