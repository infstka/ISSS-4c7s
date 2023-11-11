int dataPin = 10;
int clockPin = 11;
int latchPin = 12;
short countSec1;
short countSec2;
int nums[10] = {
  0b00000011,
  0b10011111,
  0b00100101,
  0b00001101,
  0b10011001,
  0b01001001,
  0b01000001,
  0b00011111,
  0b00000001,
  0b00001001
};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  for (countSec1 = 9; countSec1 > -1; countSec1--) {
    for (countSec2 = 9; countSec2 > -1; countSec2--) {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, nums[countSec2]);  // Правый дисплей
      shiftOut(dataPin, clockPin, LSBFIRST, nums[countSec1]);  // Левый дисплей
      digitalWrite(latchPin, HIGH);
      delay(500);
    }
  }
}
