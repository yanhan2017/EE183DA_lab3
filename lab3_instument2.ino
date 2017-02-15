#include <Servo.h>

Servo s;
int sw;

void setup() {
  s.attach(D3);
  pinMode(D1, INPUT);
  s.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  sw = analogRead(D1);
  if (sw > 200)
  {
    s.write(60);
    delay(350);
    s.write(0);
    delay(350);
  }
}
