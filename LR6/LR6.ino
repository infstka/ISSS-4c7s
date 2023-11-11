#include <Bounce2.h>;
#define PIN_BUTTON 2
#define PIN_LED 13

// Создаем объект 
Bounce debouncer = Bounce();

void setup() {

  // Устаовили тип пина
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // Даем бибилотеке знать, к какому пину мы подключили кнопку
  debouncer.attach(PIN_BUTTON);
  debouncer.interval(5); // Интервал, в течение которого мы не буем получать значения с пина

  //Setup the LED :
  pinMode(PIN_LED, OUTPUT);

}

void loop() {
  // Даем объекту бибилотеки знать, что надо обновить состояние - мы вошли в новый цкил loop
  debouncer.update();

  // Получаем значение кнопки
  int value = debouncer.read();

  // Теперь мы точно знаем, в каком состоянии находится наша кнопка
  if ( value == LOW ) {
    digitalWrite(PIN_LED, HIGH );
  }
  else {
    digitalWrite(PIN_LED, LOW );
  }
}