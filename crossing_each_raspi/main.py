import time
from RailSwitch import *
from Servo import *

SW_LEFT_PIN = 14
SW_RIGHT_PIN = 15
SV1_PIN = 23
SV2_PIN = 24
DIR_NO = 0
DIR_LR = 1
DIR_RL = 2

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
sw_left = RailSwitch(SW_LEFT_PIN)
sw_right = RailSwitch(SW_RIGHT_PIN)
sv1 = Servo(SV1_PIN)
sv2 = Servo(SV2_PIN)
dir = DIR_NO
angle = 90
epoch = 0
sv1.write(angle)
sv2.write(angle)
time.sleep(1)
sv1.stop()
sv2.stop()

try:
    while(True):
        if dir == DIR_NO and time.time() - epoch > 3:
            if sw_left.is_pushed():
                dir = DIR_LR
            if sw_right.is_pushed():
                dir = DIR_RL
        elif dir == DIR_LR and sw_right.is_pushed():
            dir = DIR_NO
            epoch = time.time()
        elif dir == DIR_RL and sw_left.is_pushed():
            dir = DIR_NO
            epoch = time.time()
        if dir != DIR_NO and angle < 180:
            angle += 1
            sv1.write(angle)
            sv2.write(angle)
        elif dir == DIR_NO and angle > 90:
            angle -= 1
            sv1.write(angle)
            sv2.write(angle)
        time.sleep(0.01)
        sv1.stop()
        sv2.stop()
except KeyboardInterrupt:
    print("break")
    sv1.write(90)
    sv2.write(90)
    time.sleep(1)
    sv1.stop()
    sv2.stop()
    GPIO.cleanup()

