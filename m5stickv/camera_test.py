# Untitled - By: wik - 水 12月 18 2019

import sensor
import lcd

lcd.init()
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.run(1)

while 1:
    img = sensor.snapshot()
    lcd.display(img)
