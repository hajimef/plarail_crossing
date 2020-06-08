#include <Servo.h>
#include "RailSwitch.h"

const int sw_leftPin = 2;
const int sw_rightPin = 3;
const int servoPin1 = 4;
const int servoPin2 = 5;
const int dir_no = 0;
const int dir_lr = 1;
const int dir_rl = 2;
Servo sv1, sv2;
volatile RailSwitch sw_left, sw_right;
int angle;
int dir;
unsigned long ms;

void sw_left_on() {
  sw_left.set_pushed();
}

void sw_right_on() {
  sw_right.set_pushed();
}

void setup() {
  pinMode(sw_leftPin, INPUT_PULLUP);
  pinMode(sw_rightPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sw_leftPin), sw_left_on, FALLING);
  attachInterrupt(digitalPinToInterrupt(sw_rightPin), sw_right_on, FALLING);
  delay(2000);
  angle = 90;
  sv1.attach(servoPin1);
  sv2.attach(servoPin2);
  sv1.write(angle);
  sv2.write(angle);
  dir = dir_no;
  ms = 0;
}
 
void loop(){
  if (dir == dir_no && millis() - ms > 3000) {
    if (sw_left.is_pushed()) {
      dir = dir_lr;
    }
    else if (sw_right.is_pushed()) {
      dir = dir_rl;
    }
  }
  else if (dir == dir_lr && sw_right.is_pushed()) {
    dir = dir_no;
    ms = millis();
  }
  else if (dir == dir_rl && sw_left.is_pushed()) {
    dir = dir_no;
    ms = millis();
  }
  if (dir != dir_no && angle < 180) {
      angle++;
      sv1.write(angle);
      sv2.write(angle);
  }
  else if (dir == dir_no && angle > 90) {
      angle--;
      sv1.write(angle);
      sv2.write(angle);
  }
  delay(15);
}
