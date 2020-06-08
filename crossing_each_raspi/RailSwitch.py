import RPi.GPIO as GPIO
import time

class RailSwitch:
    def __init__(self, pin, delay = 1000):
        self.pin = pin
        self.delay = delay / 1000
        self.pushed = False
        self.t = 0
        GPIO.setup(self.pin, GPIO.IN, pull_up_down = GPIO.PUD_UP)
        GPIO.add_event_detect(self.pin, GPIO.FALLING, callback = self.callback)

    def callback(self, ch):
        self.set_pushed()

    def set_pushed(self):
        self.t = time.time()
        self.pushed = True

    def reset_pushed(self):
        self.t = 0
        self.pushed = False

    def is_pushed(self):
        if (self.pushed):
            now = time.time()
            if (now - self.t < self.delay):
                return True
            else:
                self.reset_pushed()
                return False
        else:
            return False

