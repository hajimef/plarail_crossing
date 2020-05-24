#include <ESP32Servo.h>

#define SERVO_PIN 2

Servo sv;

void setup() {
  sv.attach(SERVO_PIN);
  sv.write(0);
  delay(1000);
  sv.write(90);
}

void loop() {
}
