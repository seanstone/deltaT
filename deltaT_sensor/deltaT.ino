#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

unsigned int l1, l2;
volatile bool d1, d2;
volatile unsigned long t1, t2;
long dt;

void setup() 
{
    Serial.begin(9600); 

    lcd.begin(16, 2);
    lcd.setRGB(80, 0, 0);

    pinMode(2, INPUT);
    pinMode(3, INPUT);
    attachInterrupt(0, change2, CHANGE);
    attachInterrupt(1, change3, CHANGE);

    d1 = digitalRead(2);
    d2 = digitalRead(3);
}

/*
void readValues()
{
    l1 = analogRead(A0);
    l2 = analogRead(A1);
    d1 = digitalRead(2);
    d2 = digitalRead(3);
    Serial.print("L1:");
    Serial.print(l1);
    Serial.print("L2:");
    Serial.print(l2);
    Serial.println("");
}

void displayValues()
{
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("L1:");
    lcd.print(l1);
    lcd.setCursor(8, 0);
    lcd.print("L2:");
    lcd.print(l2);
}

void evalThreshold()
{
    unsigned long t = millis();
    if (l1 > 700 && t1 == 0) t1 = t;
    if (l2 > 700 && t2 == 0) t2 = t;
    if (l1 < 300) { t1 = 0; dt = 0; lcd.clear(); }
    if (l2 < 300) { t2 = 0; dt = 0; lcd.clear();  }

    if (!dt && t1 > 0 && t2 > 0)
    {
        dt = t1-t2;
        lcd.setCursor(0, 1);
        lcd.print("t2-t1 = ");
        lcd.print(dt);
        lcd.print(" us");
    }
}
*/

void loop() 
{
    lcd.setCursor(0, 0);
    lcd.print("1 ");
    lcd.print(d1?"ON ":"OFF");
    lcd.setCursor(8, 0);
    lcd.print("2 ");
    lcd.print(d2?"ON ":"OFF");
    if (!dt)
    {
        lcd.setCursor(0, 1);
        lcd.print("                ");
        if (t1 && t2)
        {
            dt = t2-t1;
            lcd.setCursor(0, 1);
            lcd.print("t2-t1= ");
            float ms = dt/1000.0;
            lcd.print(ms, 3);
            lcd.print(" ms");
       }
    }
    
    // readValues();
    // displayValues();
    // evalThreshold();
}

void change2() { t1 = (d1 = !d1) ? micros() : dt = 0; }
void change3() { t2 = (d2 = !d2) ? micros() : dt = 0; }
