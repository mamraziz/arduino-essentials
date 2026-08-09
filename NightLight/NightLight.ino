int led = 13;
int ldr = 11;


void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(ldr, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(ldr) == 1) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
