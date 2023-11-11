#define RED_LED_PIN 11
#define YELLOW_LED_PIN 10
#define GREEN_LED_PIN 9

enum Mode {
  OFF,
  NORMAL,
  SLEEP,
  RED,
  GREEN
};

Mode mode = OFF;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    switch (command) {
    case 'N':
      mode = NORMAL;
      Serial.println("Включён режим normal");
      break;
    case 'S':
      mode = SLEEP;
      Serial.println("Включён режим sleep");
      break;
    case 'R':
      mode = RED;
      Serial.println("Включён режим red");
      break;
    case 'G':
      mode = GREEN;
      Serial.println("Включён режим green");
      break;
    }
  }

  switch (mode) {
  case OFF:
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    break;
  case NORMAL:
    digitalWrite(RED_LED_PIN, HIGH);
    delay(5000);
    digitalWrite(RED_LED_PIN, LOW);

    digitalWrite(YELLOW_LED_PIN, HIGH);
    delay(2000);
    digitalWrite(YELLOW_LED_PIN, LOW);

    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(5000);
    digitalWrite(GREEN_LED_PIN, LOW);

    digitalWrite(YELLOW_LED_PIN, HIGH);
    delay(2000);
    digitalWrite(YELLOW_LED_PIN, LOW);
    break;
  case SLEEP:
    digitalWrite(YELLOW_LED_PIN, HIGH);
    delay(1000);
    digitalWrite(YELLOW_LED_PIN, LOW);
    delay(1000);
    break;
  case RED:
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    break;
  case GREEN:
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    break;
  }
}