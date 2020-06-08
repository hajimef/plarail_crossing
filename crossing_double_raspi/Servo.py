import RPi.GPIO as GPIO

class Servo:
    def __init__(self, pin, min = 2.5, max = 12):
        self.pin = pin
        self.min = min
        self.max = max
        GPIO.setup(pin, GPIO.OUT)
        self.pwm = GPIO.PWM(pin, 50)
        self.pwm.start(0.0)

    def write(self, angle):
        c = self.min + (self.max - self.min) / 180 * angle
        self.pwm.ChangeDutyCycle(c)

    def stop(self):
        self.pwm.ChangeDutyCycle(0.0)
