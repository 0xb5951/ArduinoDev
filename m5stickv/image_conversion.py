import lcd, sensor, image

lcd.init()

def camera_setup():
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QQVGA)
    lcd.direction(lcd.YX_LRUD)
    sensor.run(1)

def print_string():
    img = sensor.snapshot()
    img2 = img.draw_string(30, 30, "text\ntext2")
    lcd.display(img)
    lcd.display(img2)

camera_setup()
while 1:
    print_string()
