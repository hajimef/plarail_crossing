#include "RailSwitch.h"
#include <Arduino.h>

RailSwitch::RailSwitch(void) {
  delay = 1000;
}

RailSwitch::RailSwitch(unsigned long _delay) {
  delay = _delay;
}

void RailSwitch::set_pushed(void) {
  t = millis();  
  pushed = true;
}

void RailSwitch::reset_pushed(void) {
  t = 0;
  pushed = false;
}

bool RailSwitch::is_pushed(void) {
  unsigned long now;

  if (pushed) {
    now = millis();
    if (now - t < delay) {
      return true;
    }
    else {
      reset_pushed();
      return false;
    }
  }
  else {
    return false;
  }
}
