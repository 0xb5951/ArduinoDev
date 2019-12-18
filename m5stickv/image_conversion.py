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

def save_picture_to_flash(img):
    img.save("/flash/1.bmp")     #内蔵フラッシュに保存


def save_gray_picture():
    sensor.reset()
    sensor.set_pixformat(sensor.GRAYSCALE)
    sensor.set_framesize(sensor.QQVGA)
    lcd.direction(lcd.YX_LRUD)
    sensor.run(1)

    img = sensor.snapshot()
    save_picture_to_flash(img)

'''
main function
'''
#lcd.init()
#camera_setup()
#save_gray_picture()
#print_string()


sensor.reset()
sensor.set_framesize(sensor.QQVGA)
sensor.set_pixformat(sensor.RGB565)
sensor.set_hmirror(False)
lcd.init(freq=15000000)
lcd.direction(lcd.YX_LRUD)

face_cascade = image.HaarCascade("frontalface", stages=25)
while (True):
    img = sensor.snapshot()
    img.lens_corr(1.06,zoom=1.0)
    img.draw_string(0, 0, "Looking for a face...")
    g = img.to_grayscale(copy=True)
    objects = g.find_features(face_cascade, threshold=0.5, scale=1.25)
    if objects:
        face = (objects[0][0]-31, objects[0][1]-31,objects[0][2]+31*2, objects[0][3]+31*2)
        kpts1 = g.find_keypoints(threshold=10, scale_factor=1.1, max_keypoints=100, roi=face)
        img.draw_rectangle(objects[0])
    lcd.display(img)

#while 1:
    #find_squad_in_picture()
    #lcd.display()
