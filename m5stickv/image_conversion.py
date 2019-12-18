import lcd, sensor, image

lcd.init()
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.run(1)

lcd.direction(lcd.YX_LRUD)

def print_string():
    img = sensor.snapshot()
    img2 = img.draw_string(30, 30, "text\ntext2")
    lcd.display(img)
    lcd.display(img2)

while 1:
    print_string()
