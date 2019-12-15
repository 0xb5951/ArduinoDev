from fpioa_manager import *
from Maix import GPIO
import utime

fm.register(board_info.LED_R, fm.fpioa.GPIO3)
fm.register(board_info.LED_G, fm.fpioa.GPIO4)
fm.register(board_info.LED_B, fm.fpioa.GPIO5)
fm.register(board_info.LED_W, fm.fpioa.GPIO6)

led_r = GPIO(GPIO.GPIO3, GPIO.OUT)
led_g = GPIO(GPIO.GPIO4, GPIO.OUT)
led_b = GPIO(GPIO.GPIO5, GPIO.OUT)
led_w = GPIO(GPIO.GPIO6, GPIO.OUT)

while True:
    led_r.value(0) #turn on LED
    utime.sleep(1)
    led_r.value(1)

    led_g.value(0)
    utime.sleep(1)
    led_g.value(1)

    led_b.value(0)
    utime.sleep(1)
    led_b.value(1)

    led_w.value(0)
    utime.sleep(1)
    led_w.value(1)
    utime.sleep(1)
