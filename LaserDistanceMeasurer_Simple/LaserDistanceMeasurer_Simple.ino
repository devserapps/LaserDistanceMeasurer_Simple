#include "SRF05.h"
#include <LiquidCrystal_I2C.h>
#include <Button.h>
#include <Ticker.h>

#define laser1 6
#define laser2 5
SRF05 srf(3, 2);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Button pauseBtn(4);

void updateMeasureForLCD() {
  float centimeters = srf.getCentimeter();
  float inches = centimeters * 0.3937;

  lcd.clear();

  lcd.setCursor(0, 0); 
  lcd.print(String(centimeters, 2) + " cm");

  lcd.setCursor(0, 1); 
  lcd.print(String(inches, 2) + " inch");
}

Ticker lcdTicker(updateMeasureForLCD, 200, 0, MILLIS);

void setup() {
  lcd.init();
  lcd.backlight();
  pauseBtn.begin();
  lcdTicker.start();
  pinMode(laser1, OUTPUT);
  pinMode(laser2, OUTPUT);
  digitalWrite(laser1, HIGH);
  digitalWrite(laser2, HIGH);
}

void loop() {
  lcdTicker.update();

  if (pauseBtn.pressed()) {
    if (lcdTicker.state() == RUNNING) {
      lcdTicker.pause();
      digitalWrite(laser1, LOW);
      digitalWrite(laser2, LOW);
    } else {
      lcdTicker.start();
      digitalWrite(laser1, HIGH);
      digitalWrite(laser2, HIGH);
    }
  }
}
