#include <ESP32Servo.h>
#include "RailSwitch.h"

const int sw_in1Pin = 25;
const int sw_out1Pin = 26;
const int sw_in2Pin = 32;
const int sw_out2Pin = 33;
const int servoPin1 = 2;
const int servoPin2 = 4;

Servo sv1, sv2;
RailSwitch sw_in1(sw_in1Pin), sw_out1(sw_out1Pin), sw_in2(sw_in2Pin), sw_out2(sw_out2Pin);
int angle;
bool is_passing1, is_passing2;

void setup() {
  sw_in1.begin();
  sw_out1.begin();
  sw_in2.begin();
  sw_out2.begin();
  angle = 90;
  sv1.attach(servoPin1);
  sv2.attach(servoPin2);
  sv1.write(angle);
  sv2.write(angle);
  is_passing1 = false;
  is_passing2 = false;
}
 
void loop(){
  if (sw_in1.is_pushed()) {
    is_passing1 = true;
  }
  else if (sw_out1.is_pushed()) {
    is_passing1 = false;
  }
  if (sw_in2.is_pushed()) {
    is_passing2 = true;
  }
  else if (sw_out2.is_pushed()) {
    is_passing2 = false;
  }
  if ((is_passing1 || is_passing2) && angle > 0) {
      angle--;
      sv1.write(angle);
      sv2.write(angle);
  }
  else if (!is_passing1 && !is_passing2 && angle < 90) {
      angle++;
      sv1.write(angle);
      sv2.write(angle);
  }
  delay(20);
}
