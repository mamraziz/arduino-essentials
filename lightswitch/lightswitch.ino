int led = 13;
int btn = 12;
bool on = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  Serial.begin(9600); // This is just to help troubleshoot whether we are recieving button inputs, feel free to delete if everything is working
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(btn) == LOW) {
    on = !on;
    Serial.println("pressed");  // This prints out 'pressed' whenever we click the button which helps in troubleshooting, feel free to delete. 
    delay(250);
  } 
  if (on == true) {
    digitalWrite(led, HIGH);
  }
  if (on == false) {
    digitalWrite(led, LOW);
  }
}
