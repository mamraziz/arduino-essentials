#include <Servo.h>


Servo motor;

int moter = 10;
int echo = 8;
int trig = 9;
int angle = 0;

float duration, distance;

void setup() {
  // put your setup code here, to run once:
  motor.attach(moter);
  motor.write(0);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (angle = 10; angle < 180; angle ++) {
    motor.write(angle);

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    distance = (duration*.0343)/2;

    if (distance > 5 && distance < 30) {
      Serial.println(distance);
      Serial.println("Object found");
    }
    delay(15);
  }
  for (angle = 180; angle > 10; angle --) {
    motor.write(angle);
    delay(15);
  }
}
