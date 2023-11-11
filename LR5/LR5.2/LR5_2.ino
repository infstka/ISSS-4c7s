#define LED_R_PIN 9
#define LED_G_PIN 10
#define LED_B_PIN 11

String input;

void setup() {
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);

  Serial.begin(9600);
}

void setRGBColor(int r, int g, int b) {
  analogWrite(LED_R_PIN, r);
  analogWrite(LED_G_PIN, g);
  analogWrite(LED_B_PIN, b);
}

bool parseRGBInput(String input, int & r, int & g, int & b) {
  input.trim();

  int firstCommaIndex = input.indexOf(',');
  int secondCommaIndex = input.lastIndexOf(',');

  if (firstCommaIndex == -1 || secondCommaIndex == -1) {
    return false; // Не найдена запятая, ввод некорректен
  }

  String rStr = input.substring(0, firstCommaIndex);
  String gStr = input.substring(firstCommaIndex + 1, secondCommaIndex);
  String bStr = input.substring(secondCommaIndex + 1);

  r = rStr.toInt();
  g = gStr.toInt();
  b = bStr.toInt();

  // Проверяем, что все три значения в диапазоне от 0 до 255
  return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

void loop() {
  while (Serial.available()) {
    char incoming_char = Serial.read();
    if (incoming_char != '\n') {
      input += incoming_char;
    } else {
      int r, g, b;
      if (parseRGBInput(input, r, g, b)) {
        setRGBColor(r, g, b);
      } else {
        Serial.println("Invalid input");
      }
      input = "";
    }
  }
}