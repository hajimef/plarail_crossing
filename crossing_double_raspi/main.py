import time
from RailSwitch import *
from Servo import *

SW_IN1_PIN = 14
SW_OUT1_PIN = 15
SW_IN2_PIN = 17
SW_OUT2_PIN = 18
SV1_PIN = 23
SV2_PIN = 24

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
sw_in1 = RailSwitch(SW_IN1_PIN)
sw_out1 = RailSwitch(SW_OUT1_PIN)
sw_in2 = RailSwitch(SW_IN2_PIN)
sw_out2 = RailSwitch(SW_OUT2_PIN)
sv1 = Servo(SV1_PIN)
sv2 = Servo(SV2_PIN)
is_passing1 = False
is_passing2 = False
angle = 90
sv1.write(angle)
sv2.write(angle)
time.sleep(1)
sv1.stop()
sv2.stop()

try:
    while(True):
        if sw_in1.is_pushed():
            is_passing1 = True
        if sw_out1.is_pushed():
            is_passing1 = False
        if sw_in2.is_pushed():
            is_passing2 = True
        if sw_out2.is_pushed():
            is_passing2 = False
        if (is_passing1 or is_passing2) and angle < 180:
            angle += 1
            sv1.write(angle)
            sv2.write(angle)
        elif not is_passing1 and not is_passing2 and angle > 90:
            angle -= 1
            sv1.write(angle)
            sv2.write(angle)
        time.sleep(0.01)
        sv1.stop()
        sv2.stop()
        time.sleep(0.005)
except KeyboardInterrupt:
    print("break")
    sv1.write(90)
    sv2.write(90)
    time.sleep(1)
    sv1.stop()
    sv2.stop()
    GPIO.cleanup()
