#include <Servo.h>
#include "RailSwitch.h"

const int sw_inPin = 2;
const int sw_outPin = 3;
const int servoPin1 = 4;
const int servoPin2 = 5;

Servo sv1, sv2;
volatile RailSwitch sw_in, sw_out;
int angle;
bool is_passing;

void sw_in_on() {
  sw_in.set_pushed();
}

void sw_out_on() {
  sw_out.set_pushed();
}

void setup() {
  pinMode(sw_inPin, INPUT_PULLUP);
  pinMode(sw_outPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sw_inPin), sw_in_on, FALLING);
  attachInterrupt(digitalPinToInterrupt(sw_outPin), sw_out_on, FALLING);
  delay(2000);
  angle = 90;
  sv1.attach(servoPin1);
  sv2.attach(servoPin2);
  sv1.write(angle);
  sv2.write(angle);
  is_passing = false;
}
 
void loop(){
  if (sw_in.is_pushed()) {
    is_passing = true;
  }
  else if (sw_out.is_pushed()) {
    is_passing = false;
  }
  if (is_passing && angle < 180) {
      angle++;
      sv1.write(angle);
      sv2.write(angle);
  }
  else if (!is_passing && angle > 90) {
      angle--;
      sv1.write(angle);
      sv2.write(angle);
  }
  delay(15);
}
