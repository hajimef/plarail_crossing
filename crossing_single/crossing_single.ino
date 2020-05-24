#include <ESP32Servo.h>
#include "RailSwitch.h"

const int sw_inPin = 25;
const int sw_outPin = 26;
const int servoPin1 = 2;
const int servoPin2 = 4;

Servo sv1, sv2;
RailSwitch sw_in(sw_inPin), sw_out(sw_outPin);
int angle;
bool is_passing;

void setup() {
  Serial.begin(115200);

  sw_in.begin();
  sw_out.begin();
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
  if (is_passing && angle > 0) {
      angle--;
      sv1.write(angle);
      sv2.write(angle);
  }
  else if (!is_passing && angle < 90) {
      angle++;
      sv1.write(angle);
      sv2.write(angle);
  }
  delay(20);
}
