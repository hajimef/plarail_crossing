import time
from RailSwitch import *
from Servo import *

SW_IN_PIN = 14
SW_OUT_PIN = 15
SV1_PIN = 23
SV2_PIN = 24

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
sw_in = RailSwitch(SW_IN_PIN)
sw_out = RailSwitch(SW_OUT_PIN)
sv1 = Servo(SV1_PIN)
sv2 = Servo(SV2_PIN)
is_passing = False
angle = 90
sv1.write(angle)
sv2.write(angle)
time.sleep(1)
sv1.stop()
sv2.stop()

try:
    while(True):
        if sw_in.is_pushed():
            is_passing = True
        if sw_out.is_pushed():
            is_passing = False
        if is_passing and angle < 180:
            angle += 1
            sv1.write(angle)
            sv2.write(angle)
        elif not is_passing and angle > 90:
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

