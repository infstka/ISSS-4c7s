#include <LiquidCrystal_I2C.h>
#include <arduinoFFT.h>

#define SAMPLES 64
#define SAMPLING_FREQUENCY 1000

LiquidCrystal_I2C lcd(0x27, 16, 2);
int GUITAR_IN = A0;
double frequency = 0;  //для хранения частоты

arduinoFFT FFT = arduinoFFT();  //объект FFT для выполнения преобразования Фурье

unsigned int sampling_period_us;  //период выборки
unsigned long microseconds;       //хранение времени

double vReal[SAMPLES];  //массив для хранения реальной части данных FFT
double vImag[SAMPLES];  //массив для хранения мнимой части данных FFT
String tune = "tuned";

void setup() {
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Guitar tuner");
  lcd.setCursor(0, 1);
  lcd.print("Arduino project");
  delay(2000);
  pinMode(GUITAR_IN, INPUT);
  Serial.begin(9600);
}

double FindFrequency() {
  for (int i = 0; i < SAMPLES; i++) {
    microseconds = micros();
    vReal[i] = analogRead(GUITAR_IN);
    vImag[i] = 0;
    while (micros() < (microseconds + sampling_period_us))
      ;
  }

  //FFT
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  //применение оконной функции Хэмминга к данным
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);                  //вып-е FFT
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);                    //преобразование комплексных чисел в магнитуду
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);  //определение основной частоты пика

  peak = peak * 0.990;  //корректировка
  return peak;
}

void loop() {
  frequency = FindFrequency();

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(frequency);
  lcd.setCursor(5, 1);
  lcd.print("Hz");

  //стандартные частоты для EADGBE

  //сначала if для частоты, ниже необходимой
  //затем if для частоты, выше необходимой
  //финальный if для необходимого диапазоеа частот

  //E2
  if (frequency >= 75 && frequency <= 90) {
    if (frequency < 81.5) {
      lcd.setCursor(0, 0);
      lcd.print("  <<<  E2       ");
    }
    if (frequency > 83.5) {
      lcd.setCursor(0, 0);
      lcd.print("       E2  >>>  ");
    }
    if (frequency >= 81.5 && frequency <= 83.5) {
      //lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("E2");
      lcd.setCursor(11, 1);
      lcd.print(tune);
    }
  }
  //A2
  else if (frequency <= 120.00 && frequency >= 100.00) {
    if (frequency < 108.00) {
      lcd.setCursor(0, 0);
      lcd.print("  <<<  A2       ");
    }
    if (frequency > 112.00) {
      lcd.setCursor(0, 0);
      lcd.print("       A2  >>>  ");
    }
    if (frequency >= 108.00 && frequency <= 112.00) {
      //lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("A2");
      lcd.setCursor(11, 1);
      lcd.print(tune);
    }
  }
  //D3
  else if (frequency >= 130.00 && frequency <= 150.00) {
    if (frequency < 145) {
      lcd.setCursor(0, 0);
      lcd.print("  <<<  D3       ");
    }
    if (frequency > 148) {
      lcd.setCursor(0, 0);
      lcd.print("       D3  >>>  ");
    }
    if (frequency >= 145 && frequency <= 148) {
      //lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("D3");
      lcd.setCursor(11, 1);
      lcd.print(tune);
    }
  }
  //G3
  else if (frequency >= 180.00 && frequency <= 210.00) {
    if (frequency < 193.00) {
      lcd.setCursor(0, 0);
      lcd.print("  <<<  D3       ");
    }
    if (frequency > 199.00) {
      lcd.setCursor(0, 0);
      lcd.print("       A2  >>>  ");
    }
    if (frequency >= 193.00 && frequency <= 199.00) {
      //lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("G3");
      lcd.setCursor(9, 1);
      lcd.print(tune);
    }
  }
  //B3
  else if (frequency >= 230.00 && frequency <= 260.00) {
    if (frequency < 246) {
      lcd.setCursor(0, 0);
      lcd.print("  <<<  B3       ");
    }
    if (frequency > 251) {
      lcd.setCursor(0, 0);
      lcd.print("       B3  >>>  ");
    }
    if (frequency >= 245 && frequency <= 251) {
      //lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("B3");
      lcd.setCursor(10, 1);
      lcd.print(tune);
    }
  }
  //E4
  else if (frequency >= 310.00 && frequency <= 355.00) {
    if (frequency < 328) {
      lcd.setCursor(0, 0);
      lcd.print("  <<<  E4       ");
    }
    if (frequency > 334) {
      lcd.setCursor(0, 0);
      lcd.print("       E4  >>>  ");
    }
    if (frequency >= 328 && frequency <= 334) {
      //lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("E4");
      lcd.setCursor(10, 1);
      lcd.print(tune);
    }
  }

  //частоты обертонов (частоты, выше основного тона)

  //A3
  else if (frequency <= 240 && frequency >= 200) {
    if (frequency < 218) {
      lcd.setCursor(0, 0);
      lcd.print("  <<<  A2       ");
    }
    if (frequency > 224) {
      lcd.setCursor(0, 0);
      lcd.print("       A2  >>>  ");
    }
    if (frequency >= 218 && frequency <= 224) {
      //lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("A2");
      lcd.setCursor(10, 1);
      lcd.print(tune);
    }
  }
  //D4
  else if (frequency <= 309 && frequency >= 280) {
    if (frequency < 292) {
      lcd.setCursor(0, 0);
      lcd.print("  <<<  D3       ");
    }
    if (frequency > 299) {
      lcd.setCursor(0, 0);
      lcd.print("       D3  >>>  ");
    }
    if (frequency >= 292 && frequency <= 299) {
      lcd.setCursor(7, 0);
      lcd.print("D3");
      lcd.setCursor(10, 1);
      lcd.print(tune);
    }
  }
  //G4
  else if (frequency <= 410 && frequency >= 370) {
    if (frequency < 389) {
      lcd.setCursor(0, 0);
      lcd.print("  <<<  G3       ");
    }
    if (frequency > 397) {
      lcd.setCursor(0, 0);
      lcd.print("       G3  >>>  ");
    }
    if (frequency >= 389 && frequency <= 397) {
      //lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("G3");
      lcd.setCursor(9, 1);
      lcd.print(tune);
    }
  }
  //B4
  else if (frequency <= 510 && frequency >= 480) {
    if (frequency < 490) {
      lcd.setCursor(0, 0);
      lcd.print("  <<<  B3       ");
    }
    if (frequency > 500) {
      lcd.setCursor(0, 0);
      lcd.print("       B3  >>>  ");
    }
    if (frequency >= 490 && frequency <= 500) {
      //lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("B3");
      lcd.setCursor(9, 1);
      lcd.print(tune);
    }
  }

  delay(500);
}