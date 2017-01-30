#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

int triggerPort = 7;
int echoPort = 8;
int buzzer = 9;

unsigned long time;
unsigned long lampeggio_time;
unsigned long pausa_time;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(triggerPort, OUTPUT);
  pinMode(echoPort, INPUT);
  pinMode(buzzer, OUTPUT);
  lcd.setCursor(0, 1);
  lcd.print("  Sensore  HC-SR04  ");
  delay(2500);
  lcd.clear();
}

void loop() {
  digitalWrite(triggerPort, LOW);
  digitalWrite(triggerPort, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPort, LOW);
  long duration = pulseIn(echoPort, HIGH);
  long r = 0.034 * duration / 2;
  lcd.setCursor(0, 1);
  lcd.print("Distanza: ");

  if (duration > 38000) {
    lcd.setCursor(0, 1);
    lcd.print("     null    ");
  }

  else {
    lcd.print(r);
    lcd.print("  cm  ");
  }

  if (r > 3 && r <= 200) {
    delay(r * 10);
    digitalWrite(buzzer, HIGH);
    tone(buzzer, 2000);
    delay(r * 10);
  }

  if ( r <= 3) {
    digitalWrite(buzzer, HIGH);
    tone(buzzer, 2000);    
    delay(50);
  }

  digitalWrite(buzzer, LOW);
  noTone(buzzer);
  delay(10);
}

