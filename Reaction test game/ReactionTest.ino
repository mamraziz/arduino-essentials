#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int buzzer = 11;
int ref = 10;
int p1 = 2;
int p2 = 3; 
bool pressed = false;

int sp1 = 0;
int sp2 = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Reaction game");

  pinMode(buzzer, OUTPUT);
  pinMode(ref, OUTPUT); 
  pinMode(p1, INPUT_PULLUP);
  pinMode(p2, INPUT_PULLUP);
  Serial.begin(9600);  
}

void loop() {
  //reset
  delay(2000);
  pressed = false;
  digitalWrite(ref, LOW);
  lcd.setCursor(0,0);
  lcd.print("Ready?");
  lcd.print("          ");
  lcd.setCursor(0,1);
  lcd.print("              ");

  // Countdown
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(200);

  // wait a random time
  lcd.setCursor(0,0);
  lcd.print("Wait for it...");
  lcd.print("          ");
  delay(random(4000,12000)); 

  if (digitalRead(p1) == LOW || digitalRead(p2) == LOW) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("DO NOT HOLD");
    lcd.print("     ");
    lcd.setCursor(0,1);
    lcd.print(" THE BUTTON");
    lcd.print("     ");
    digitalWrite(buzzer, HIGH);
    delay(2000);
    digitalWrite(buzzer, LOW);
    return;
  }

  digitalWrite(ref, HIGH);
  lcd.setCursor(0,0);
  lcd.print("NOW!");
  lcd.print("          ");

  while (!pressed) {
    if (digitalRead(p1) == LOW) {
    delay(20); // ensure its not an electrical issue 
      if (digitalRead(p1) == LOW) {
        pressed = true;
        trigger(1);
      }
    }
    if (digitalRead(p2) == LOW) {
    delay(20);
      if (digitalRead(p2) == LOW) {
        pressed = true;
        trigger(2);
      }
    }
  }

}

void trigger(int p) {
  if (p == 1) {
    Serial.println("Player 1");
    sp1 += 1;
    scoreboard(1);
    digitalWrite(ref, LOW);
    digitalWrite(buzzer, HIGH);
    delay(500); // Other player cant play
    digitalWrite(buzzer, LOW);
  }
  if (p == 2) {
    Serial.println("Player 2");
    sp2 +=1; 
    scoreboard(2);
    digitalWrite(ref, LOW);
    digitalWrite(buzzer, HIGH);
    delay(500); // Other player cant play
    digitalWrite(buzzer, LOW);
  }
}

void scoreboard(int victor) {
  lcd.setCursor(0,0);
  lcd.print("Player 1: " + String(sp1));
  lcd.setCursor(0,1);
  lcd.print("Player 2: " + String(sp2));
  if (victor == 1) {
    lcd.setCursor(10, 0);
    lcd.print(sp1);
    lcd.print("   ");
  }
    if (victor == 2) {
    lcd.setCursor(10, 1);
    lcd.print(sp2);
    lcd.print("   ");
  }
}
