import sensor,lcd,image

sensor.reset()
sensor.set_framesize(sensor.QQVGA)
sensor.set_pixformat(sensor.RGB565)
sensor.set_hmirror(False)
lcd.init(freq=30000000)
lcd.direction(lcd.YX_LRUD)

face_cascade = image.HaarCascade("frontalface", stages=40)
while (True):
    img = sensor.snapshot()
    img.draw_string(0, 0, "Looking for a face...")
    g = img.to_grayscale(copy=True)
    objects = g.find_features(face_cascade, threshold=0.5, scale=1.25)
    if objects:
        face = (objects[0][0]-31, objects[0][1]-31,objects[0][2]+31*2, objects[0][3]+31*2)
        kpts1 = g.find_keypoints(threshold=10, scale_factor=1.1, max_keypoints=100, roi=face)
        print(kpts1)
        img.draw_rectangle(objects[0])
    lcd.display(img)



