import lcd, sensor, image

'''
function define
'''
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

def find_squad_in_picture():
    img = sensor.snapshot()
    obj = img.find_rects()
    lcd.display(img)
    # better file output
    print(obj)

'''
main function
'''
lcd.init()
camera_setup()
while 1:
    find_squad_in_picture()
