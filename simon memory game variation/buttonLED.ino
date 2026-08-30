int btn1 = 4;
int btn2 = 2;
int btn3 = 5;
int btn4 = 3;
int btn5 = 6;
int btn[5] = {4, 2, 5, 3, 6};

int led[5] = {12, 11, 10, 9, 8};
int led1 = 12;
int led2 = 11;
int led3 = 10;
int led4 = 9;
int led5 = 8;

int pattern[15] = {};
int randNum = 0;
int position = 0;
int pressedbtn = -1;
int patternpos = 0;
bool finishedRound = false; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(btn5, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(3000);
  finishedRound = false;
  randNum = random(0,5);
  pattern[position] = randNum;
  position += 1;

  for (int i = 0; i < position; i++) {
    digitalWrite(led[pattern[i]], HIGH);
    delay(1000);
    digitalWrite(led[pattern[i]], LOW);
    delay(300);
  }

  while (!finishedRound) {
    if (patternpos == position) {
      finishedRound = true;
    }
    if (digitalRead(btn1) == LOW) {
      pressedbtn = 0;
      Serial.println("btn 1");
    }
    if (digitalRead(btn2) == LOW) {
      pressedbtn = 1;
      Serial.println("btn 2");
    }
    if (digitalRead(btn3) == LOW) {
      pressedbtn = 2;
      Serial.println("btn 3");
    }
    if (digitalRead(btn4) == LOW) {
      pressedbtn = 3;
      Serial.println("btn 4");
    }
    if (digitalRead(btn5) == LOW) {
      pressedbtn = 4;
      Serial.println("btn 5");
    }
    
    if (pressedbtn != -1) {
      if (pressedbtn == pattern[patternpos]) {
        //button right
        delay(500);
        pressedbtn = -1;
        patternpos += 1;
        Serial.println("correct btn"); 
      }
      else {
        Serial.println("wrong btn"); 
        lose();
        pressedbtn = -1;
        patternpos = 0;
        position = 0;
        finishedRound = true;
      }
    }
  }

  patternpos = 0;

  delay(3000);
}

void lose() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(led[i], HIGH); 
  }
  delay(5000);
  for (int i = 0; i < 5; i++) {
    digitalWrite(led[i], LOW); 
  }
  delay(5000);
}
