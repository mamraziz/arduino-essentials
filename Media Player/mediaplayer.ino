#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int btn1 = 11;
int btn2 = 10;
int btn3 = 9;
int btn4 = 8;

String recieved;
bool playing;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  playing = false;
}

void loop() {
  if (Serial.available() > 0) {
    recieved = Serial.readStringUntil('\n');  // Reads until newline
    playing = true;
    updateUI();
  }
  // put your main code here, to run repeatedly:
  if (digitalRead(btn1) == LOW) {
    Serial.println("b");
    delay(300);
  }
  if (digitalRead(btn2) == LOW) {
    Serial.println("p");
    delay(300);
  }
    if (digitalRead(btn3) == LOW) {
    Serial.println("f");
    delay(300);
  }
    if (digitalRead(btn4) == LOW) {
    Serial.println("v");
    delay(300);
  }
  

}


void updateUI() {
  display.stopscroll();
  display.clearDisplay();
  display.setTextColor(WHITE);
  
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Now Playing");
  display.drawLine(0, 10, 127, 10, WHITE);
  display.setCursor(0, 16);
  display.setTextSize(2);
  
  if (recieved.length() > 12) {
    int splitPos = recieved.lastIndexOf(' ', 11);
    if (splitPos == -1) {
      splitPos = 11;
    }
    
    display.println(recieved.substring(0, splitPos));
    display.setCursor(0, 38);
    display.println(recieved.substring(splitPos + 1));
  } else {
    display.println(recieved);
  }
  
  display.display();
}
