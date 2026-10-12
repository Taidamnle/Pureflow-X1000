#define trigPin 7
#define echoPin 6
#define buzzer 3
#define pumpPin 9

int sound = 250;
unsigned long previousMillis = 0;
const unsigned long pumpInterval = 4000;
bool pumpState = false;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pumpPin, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance <= 5) {
    sound = 50;
  } 
  else if (distance <= 10) {
    sound = 100;
  } 
  else if (distance <= 15) {
    sound = 200;
  } 
  else if (distance <= 20) {
    sound = 300;
  } 
  else if (distance <= 25) {
    sound = 400;
  } 
  else if (distance <= 30) {
    sound = 500;
  } 
  else {
    sound = 0;
  }

  if (distance > 30 || distance <= 0) {
    Serial.println("Out of range");
    noTone(buzzer);
  } else {
    Serial.print(distance);
    Serial.println(" cm");
    tone(buzzer, sound);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= pumpInterval) {
    previousMillis = currentMillis;
    pumpState = !pumpState;
    digitalWrite(pumpPin, pumpState ? HIGH : LOW);
  }

  delay(500);
}
