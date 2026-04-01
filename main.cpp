#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define trigPin 9
#define echoPin 10
#define buzzer 8

LiquidCrystal_I2C lcd(0x27, 16, 2);

float tinggiArea = 20.0;
float safeZone = 10.0;
float dangerZone = 15.0;

void setup() {
    Serial.begin(9000);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buzzer, OUTPUT);

    lcd.init();
    lcd.backlight();
    lcd.print("Water Monitoring")
    delay(2000);
    lcd.clear();
}

void loop() {
    digitalWritter(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.034 / 2;
    float waterLevel = tinggiArea - distance;

    // tampilin ketinggian
    lcd.setCursor(0, 0);
    lcd.print("Water Level: ");
    lcd.print(waterLevel);
    lcd.print(" cm");

    // status level
    lcd.setCursor(0, 1);

    if (waterLevel < safeZone) {
        lcd.print("Status: Safe   ");
        digitalWrite(buzzer, LOW);
    } else if (waterLevel < dangerZone) {
        lcd.print("Status: Warning");
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(500);
    } else {
        lcd.print("Status: Danger ");
        digitalWrite(buzzer, HIGH);
    }
}