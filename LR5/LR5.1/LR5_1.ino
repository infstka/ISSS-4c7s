#define LED_PIN 9

String input;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

bool isNumeric(String str) {
  for (char c: str) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}

void processInput(String input) {
  input.trim(); // Удаляем лишние пробелы из ввода и приводим к нижнему регистру
  if (input == "on") {
    digitalWrite(LED_PIN, HIGH); // Включить светодиод
  } else if (input == "off") {
    digitalWrite(LED_PIN, LOW); // Выключить светодиод
  } else if (isNumeric(input)) {
    int value = input.toInt();
    if (value >= 0 && value <= 255) {
      analogWrite(LED_PIN, value);
    } else {
      Serial.println("Invalid input");
    }
  } else {
    Serial.println("Invalid input");
  }
}

void loop() {
  while (Serial.available()) {
    char incomingChar = Serial.read();
    if (incomingChar != '\n') {
      input += incomingChar;
    } else {
      processInput(input); // Обработка введенной строки
      input = ""; // Очистка строки для следующего ввода
    }
  }
}