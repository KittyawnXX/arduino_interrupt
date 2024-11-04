#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
const int led1 = 6;

String message = "TUA DAN MUDA DI KEWER KEWER  ";
int messageLength = message.length();
int displayLength = 16;
int position = 0;

bool interrupted = false;

void ISR_INT0() {
  interrupted = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MANG EAK");
  digitalWrite(led1, HIGH);
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
  lcd.begin(16, 2);

  attachInterrupt(digitalPinToInterrupt(2), ISR_INT0, CHANGE);
}

void loop() {
  if (interrupted) {
    digitalWrite(led1, HIGH);
    delay(50);
    digitalWrite(led1, LOW);
    delay(50);
  } else {
    lcd.clear();
    if (position < 0) {
      lcd.setCursor(displayLength - 1, 0);
      lcd.print(message.charAt(0));
      delay(1000);
      position = 0;
    } else {
      lcd.print(message.substring(position, position + displayLength));
    }

    position++;

    if (position > messageLength) {
      position = -1;
    }

    delay(300);
  }

  if (digitalRead(2) == HIGH && interrupted) {
    interrupted = false;
    digitalWrite(led1, LOW);
  }
}
