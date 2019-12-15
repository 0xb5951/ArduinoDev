from fpioa_manager import *
from Maix import GPIO
import utime

fm.register(board_info.LED_W, fm.fpioa.GPIO3)
led_w = GPIO(GPIO.GPIO3, GPIO.OUT)

while True:
    led_w.value(0) #turn on LED
    utime.sleep(1)
    led_w.value(1)
    utime.sleep(1)
