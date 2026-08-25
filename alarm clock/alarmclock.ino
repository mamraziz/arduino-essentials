// HEY WHEN UPLOADING OR CONNECTING THERE IS A CHANCE OF RTC BREAKING. JUST RECONNECT UNTIL YOU SOLDER
// LINE IN SETUP HAS A COMMENT SAYING TO COMMENT IT OUT


#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int alarmBtn = 4;
int btn1 = 5;
int btn2 = 6;
int buzzer = 9;

int alarmHr = 5;       
int alarmMin = 58;
int hour = 5;
int min = 57;
int seconds = 44;
bool alarmRang = false;
int prevHour = -1;
int prevMin = -1;
int prevSec = -1;
bool colon = false;
bool light = true;
bool alarmSet = true;
bool isPm = false;

// BELL ICON
byte bell[8] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00000,
  B00100,
  B00000
};

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.createChar(0, bell);

  pinMode(alarmBtn, INPUT_PULLUP);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  // 1. START the RTC first
  if (!rtc.begin()) {
    lcd.clear();
    lcd.print("RTC Error!");
    while (1); 
  }

  // 2. NOW adjust the time  COMMENT OUT BEFORE SOLDERING
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  // put your main code here, to run  repeatedly:
  DateTime now = rtc.now(); // Ask the RTC for the time
  hour = now.hour();
  min = now.minute();
  seconds = now.second();

  // Less screen update
  if (hour != prevHour || min != prevMin || seconds != prevSec) {
      updateLCD(hour, min, seconds);
      prevHour = hour;
      prevMin = min;
      prevSec = seconds;
  }

  // Manually turn of backlight
  if (digitalRead(btn2) == LOW && alarmRang == false) {
    if (light == false) {
      lcd.backlight(); 
      light = !light;
    } else {
      lcd.noBacklight(); 
      light = !light;
    }
  }

  // Manually turn off alarm
  if (digitalRead(btn1) == LOW && !alarmRang) {
    delay(150); // simple debounce
    alarmSet = !alarmSet;
    while(digitalRead(btn1) == LOW); // wait for release
}
  
  // alarm functionality
  if (digitalRead(alarmBtn) == LOW) {
    alarmMode();
  }

  if (hour == alarmHr && min == alarmMin && !alarmRang && alarmSet) {
    lcd.backlight();
    lcd.clear();
    lcd.print("SNOOZE   DISMISS");
    while (alarmRang == false) {
      // buzzer
          analogWrite(buzzer, 50);
          delay(150);       // beep duration
          analogWrite(buzzer, 0);

      if (digitalRead(btn1) == LOW) { // Snooze
        alarmHr = hour;
        alarmMin = (min + 5) % 60;
        if (min + 5 >= 60) {
              alarmHr = (hour + 1) % 24;
        }
          alarmRang = true;
          while(digitalRead(btn1) == LOW); // wait for release
      }
      if (digitalRead(btn2) == LOW) { // Dismiss alarm
        alarmRang = true;
      }
      delay(150);       // gap between beeps
    }
    lcd.clear();
  }

  if (min != alarmMin) {
    alarmRang = false;
  }

}

void updateLCD(int hour, int minute, int second) {
  int displayHour = hour;
  isPm = (hour >= 12);

  if (displayHour == 0) {
    displayHour = 12;
  } else if (displayHour > 12) {
    displayHour -= 12;
  }

  lcd.setCursor(0,0);
  lcd.print("   ");
  if (displayHour < 10) {
    lcd.print("0");
    lcd.print(displayHour);
  } else {  
    lcd.print(displayHour);
  }
  if (colon) {
    lcd.print(":");
  } else {
    lcd.print(" ");
  }
  if (minute < 10) {
    lcd.print("0");
    lcd.print(minute);
  } else {  
    lcd.print(minute);
  }
  if (colon) {
    lcd.print(":");
  } else {
    lcd.print(" ");
  }
  if (second < 10) {
    lcd.print("0");
    lcd.print(second);
  } else {  
    lcd.print(second);
  } 
  lcd.print(" ");
  if (isPm) {
    lcd.print("PM");
  } else {
    lcd.print("AM");
  }
  lcd.print("       ");

  // Show alarm
  if (alarmSet == true) {
    lcd.setCursor(0,1);
    lcd.print("Alarm ");
    if (alarmHr < 10) {
      lcd.print("0");
      lcd.print(alarmHr);
    }
    else {
      lcd.print(alarmHr);
    }
    if (colon) {
      lcd.print(":");
    } else {
      lcd.print(" ");
    }

    if (alarmMin < 10) {
      lcd.print("0");
      lcd.print(alarmMin);
    } else {
      lcd.print(alarmMin);
    }
    lcd.print(" ");
    lcd.write(byte(0));
  } else {
    lcd.setCursor(0,1);
    lcd.print("Alarm not set");
  }
  

  colon = !colon;
}

void alarmMode() {
  int hr = alarmHr;
  int min = alarmMin;
  while (digitalRead(alarmBtn) == LOW) {
    delay(10);
  }

  lcd.clear();

  while (digitalRead(alarmBtn) == HIGH) {
      lcd.setCursor(0,0);
      lcd.print("    Set Alarm");
      lcd.print("             ");
      lcd.setCursor(0,1);
      lcd.print("    ");
      if (hr < 10) {
        lcd.print("0");
        lcd.print(hr);
      } else {
        lcd.print(hr);
      }
      
      lcd.print(":");
    
      if (min < 10) {
        lcd.print("0");
        lcd.print(min);
      } else {
        lcd.print(min);
      }

      lcd.print("         ");
      if (digitalRead(btn1) == LOW) {
        if (hr < 23) {
          hr++;
        } else {
          hr = 0;
        }
      } else if (digitalRead(btn2) == LOW) {
        if (min < 59) {
          min++;
        } else {
          min = 0;
        }
      }
      delay(200);
  }
  alarmHr = hr;
  alarmMin = min;
  lcd.clear();
  alarmSet = true;
}
