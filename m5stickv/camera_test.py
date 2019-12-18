import sensor
import lcd

lcd.init()
# camera setup
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.run(1)

# LCD direction controll
lcd.direction(lcd.YX_LRUD)

while 1:
    img = sensor.snapshot()
    lcd.display(img)
