#include <Servo.h>
#include "RailSwitch.h"

const int sw_in1Pin = 2;
const int sw_out1Pin = 3;
const int sw_in2Pin = 18;
const int sw_out2Pin = 19;
const int servoPin1 = 4;
const int servoPin2 = 5;

Servo sv1, sv2;
volatile RailSwitch sw_in1, sw_out1, sw_in2, sw_out2;
int angle;
bool is_passing1, is_passing2;

void sw_in1_on() {
  sw_in1.set_pushed();
}

void sw_out1_on() {
  sw_out1.set_pushed();
}

void sw_in2_on() {
  sw_in2.set_pushed();
}

void sw_out2_on() {
  sw_out2.set_pushed();
}

void setup() {
  pinMode(sw_in1Pin, INPUT_PULLUP);
  pinMode(sw_out1Pin, INPUT_PULLUP);
  pinMode(sw_in2Pin, INPUT_PULLUP);
  pinMode(sw_out2Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sw_in1Pin), sw_in1_on, FALLING);
  attachInterrupt(digitalPinToInterrupt(sw_out1Pin), sw_out1_on, FALLING);
  attachInterrupt(digitalPinToInterrupt(sw_in2Pin), sw_in2_on, FALLING);
  attachInterrupt(digitalPinToInterrupt(sw_out2Pin), sw_out2_on, FALLING);
  delay(2000);
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
  if ((is_passing1 || is_passing2) && angle < 180) {
      angle++;
      sv1.write(angle);
      sv2.write(angle);
  }
  else if (!is_passing1 && !is_passing2 && angle > 90) {
      angle--;
      sv1.write(angle);
      sv2.write(angle);
  }
  delay(15);
}
