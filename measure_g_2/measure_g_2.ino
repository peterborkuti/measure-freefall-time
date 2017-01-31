#define VERSION "2.2"

// Both pins are normally HIGH
// START_PIN goes LOW when ball goes through between the IR LED and the phototransistor
#define START_PIN 3
// STOP_PIN goes LOW when ball hits the ground (and pushes one of the buttons)
#define STOP_PIN 2

// ADJUST THIS FOR YOUR EXPERIMENT
// Measure the distance between the first measuring point and 
// the falling point (where you eject the ball) in meters
const float d = 0.1; // 0.1 : 10 centimeters

const float g = 9.80665;

// the velocity of the falling object at the first measuring point
const float v0 = sqrt(2 * d * g);

int printCounter = 0;

unsigned long timer = 0;      // millis when ball start to fall down
unsigned long elapsedTime = 0;// millis between ball start and stop

void setup() {
  Serial.begin(9600);

  pinMode(START_PIN, INPUT);
  pinMode(STOP_PIN, INPUT);

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
 
    //elapsed time in millis, print it in seconds
    float et = (float)elapsedTime / 1000.0;
    Serial.print(et, 3);
    Serial.print(" sec. s = ");
 
    // the length of free fall is v0*t + g/2*t^2
    float s = v0 * et + g / 2.0 * et * et;
    Serial.println(s, 3);
}

void loop() {
  if (digitalRead(START_PIN) == LOW) {
    timer = millis();
 
    digitalWrite(13, HIGH);
 
    while (digitalRead(STOP_PIN) == HIGH);
  
    elapsedTime = millis() - timer;
  
    digitalWrite(13, LOW);
 
    printData();
  }
}

