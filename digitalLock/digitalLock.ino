#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char pin[4] = {};
char guess[4] = {};
int failed = 0;
int position = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  setPin();
}

void loop() {
  // put your main code here, to run repeatedly:
  enterPin();
}

void enterPin() {
  if (failed > 4) {
    fail();
  }

  lcd.setCursor(0, 0);
  lcd.print("Enter pin: ");

  char key;
  for (int i = 0; i < 4; i ++) {
    char key = keypad.waitForKey();
    if (key == 'A') {
      verify();
      return();
    } else {
      guess[i] = key;
    }
  }

  bool match = true;

  for (int i = 0; i < 4; i++) {
    if (guess[i] != pin[i]) {
      match = false;
    }
  }

  if (match) {
    success();
    failed = 0;
  }
  if (!match) {
    failed +=1;
    lcd.setCursor(0, 0);
    lcd.print("Incorrect.      ");
    delay(1000);
  }
}

void verify() {
  lcd.setCursor(0, 0);
  lcd.print("Previous pin:       ");
  bool match = true;


  for (int i = 0; i < 4; i ++) {
    char key = keypad.waitForKey();
    guess[i] = key;
  }

  for (int i = 0; i < 4; i++) {
    if (guess[i] != pin[i]) {
      match = false;
    }
  }

  if (match) {
    setPin();
    failed = 0;
  }
  if (!match) {
    failed +=1;
    lcd.setCursor(0, 0);
    lcd.print("Incorrect.     ");
    delay(1000);
  }
}

void setPin() {
  lcd.setCursor(0, 0);
  lcd.print("Set new pin:      ");
  for (int i = 0; i < 4; i ++) {
    pin[i] = keypad.waitForKey();
  }
}




void success() {
  lcd.setCursor(0, 0);
  lcd.print("Correct!       ");
  delay(5000);
}

void fail() {
  lcd.setCursor(0, 0);
  lcd.print("Locked out.    ");
  delay(60000);
  failed = 0;
}
