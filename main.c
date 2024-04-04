#define SENSOR1_PIN 2
#define SENSOR2_PIN 3
#define ENA_PIN 5
#define ENB_PIN 6
#define IN1_PIN 7
#define IN2_PIN 8
#define IN3_PIN 9
#define IN4_PIN 10

volatile int pulseCount1 = 0;
volatile int pulseCount2 = 0;

void setup() {
  pinMode(SENSOR1_PIN, INPUT_PULLUP);
  pinMode(SENSOR2_PIN, INPUT_PULLUP);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(SENSOR1_PIN), countPulse1, FALLING);
  attachInterrupt(digitalPinToInterrupt(SENSOR2_PIN), countPulse2, FALLING);
}

void loop() {
  int speed1 = pulseCount1;
  int speed2 = pulseCount2;

  pulseCount1 = 0;
  pulseCount2 = 0;

  if (speed1 == 0 && speed2 == 0) {
    // Both wheels are locked, apply ABS
    analogWrite(ENA_PIN, 0);
    analogWrite(ENB_PIN, 0);
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, LOW);
    delay(100);
    analogWrite(ENA_PIN, 255);
    analogWrite(ENB_PIN, 255);
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
    delay(50);
  } else {
    // Normal braking
    analogWrite(ENA_PIN, 255);
    analogWrite(ENB_PIN, 255);
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
  }

  delay(100);
}

void countPulse1() {
  pulseCount1++;
}

void countPulse2() {
  pulseCount2++;
}