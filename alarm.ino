#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int sw1 = 9, sw2 = 10, sw3 = 7;
const int reset = 6;
const int buzz = 8;
int sw1_state, sw2_state, sw3_state;
int minute = 0;
int hour = 1;
int alarmMinute = 0;
int alarmHour = 1;
int state = 0;
const int maxmin = 59;
const int maxhour = 12;
int secs = 0;
bool snooze = true;
int alm = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  pinMode(sw1, INPUT);
  digitalWrite(reset, HIGH);
  pinMode(reset, OUTPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
  pinMode(buzz, OUTPUT);
  lcd.home();
  Serial.begin(9600);
}

void loop() {
  sw1_state = digitalRead(sw1);
  sw2_state = digitalRead(sw2);
  sw3_state = digitalRead(sw3);
  if (state == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Set Minute:");
    lcd.setCursor(0, 1);
    lcd.print(minute);
    if (sw1_state == HIGH) {
      minute += 1;
      delay(150);
      if (minute > maxmin) {
        minute = 0;
        lcd.setCursor(1, 1);
        lcd.print(" ");
      }
    }
    else if (sw2_state == HIGH) {
      delay(150);
      state += 1;
      lcd.clear();
    }
  }
  else if (state == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Set Hour:");
    lcd.setCursor(0, 1);
    lcd.print(hour);
    if (sw1_state == HIGH) {
      hour += 1;
      delay(150);
      if (hour > maxhour) {
        hour = 1;
        lcd.setCursor(1, 1);
        lcd.print(" ");
      }
    }
    else if (sw2_state == HIGH) {
      delay(150);
      state += 1;
      lcd.clear();
    }
  }
  else if (state == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Set Alarm Min:");
    lcd.setCursor(0, 1);
    lcd.print(alarmMinute);
    if (sw1_state == HIGH) {
      alarmMinute += 1;
      delay(150);
      if (alarmMinute > maxmin) {
        alarmMinute = 0;
        lcd.setCursor(1, 1);
        lcd.print(" ");
      }
    }
    else if (sw2_state == HIGH) {
      delay(150);
      state += 1;
      lcd.clear();
    }
  }
  else if (state == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Set Alarm Hour:");
    lcd.setCursor(0, 1);
    lcd.print(alarmHour);
    if (sw1_state == HIGH) {
      alarmHour += 1;
      delay(150);
      if (alarmHour > maxhour) {
        alarmHour = 1;
        lcd.setCursor(1, 1);
        lcd.print(" ");
      }
    }
    else if (sw2_state == HIGH) {
      delay(150);
      state += 1;
      lcd.clear();
    }
  }
  else if (state == 4) {
    lcd.setCursor(0, 0);
    lcd.print(hour);
    lcd.print(":");
    Serial.println(secs);
    secs += 1;
    if (secs == 1200 * 8) {
      secs = 0;
      minute += 1;
      if (minute > maxmin) {
        minute = 0;
        hour += 1;
      }
      if (hour > maxhour) {
        hour = 1;
        minute = 0;
      }
    }
    if (minute < 9) {
      if (hour < 9) {
        lcd.setCursor(2, 0);
        lcd.print(0);
        lcd.print(minute);
      }
      else {
        lcd.setCursor(3, 0);
        lcd.print(0);
        lcd.print(minute);
      }
    }
    else {
      lcd.setCursor(2, 0);
      lcd.print(minute);
    }
    if (hour == alarmHour && minute == alarmMinute && alm == 1) {
      digitalWrite(buzz, HIGH);
    }
    if (sw3_state == HIGH) {
      digitalWrite(buzz, LOW);
      alm = 1;
    }
    if (sw1_state == HIGH && sw2_state == HIGH) {
      digitalWrite(reset, LOW);
    }
  }
}