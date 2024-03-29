#include <math.h>

int minute = 1;
#define TERMIST_B 4300
#define VIN 5.0
void setup() {
  Serial.begin(9600);
  Serial.println("CLEARDATA"); // Очистить предыдущие данные
  Serial.println("LABEL,Minute,Temperature"); // Установить заголовки столбцов
}
void loop() {
  float voltage = analogRead(A0) * VIN / 1024.0;
  float r1 = voltage / (VIN - voltage);
  float temperature = 1. / (1. / (TERMIST_B) * log(r1) + 1. / (25. + 273.)) - 273;
  Serial.print("DATA,"); // Начало строки данных
  Serial.print(minute);
  Serial.print(",");
  Serial.println(temperature);
  delay(600);
  ++minute;
}