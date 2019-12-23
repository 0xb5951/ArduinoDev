## This Source is M5StickV MaixPy
import network, socket, time, sensor, image,lcd
from Maix import GPIO
from fpioa_manager import fm, board_info
from machine import UART

#M5StickV Camera Start
clock = time.clock()
lcd.init()
sensor.reset()
sensor.set_framesize(sensor.QQVGA)
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.run(1)
sensor.skip_frames(time = 2000)
# LCD direction controll
lcd.direction(lcd.YX_LRUD)

#M5StickV GPIO_UART
fm.register(35, fm.fpioa.UART2_TX, force=True)
fm.register(34, fm.fpioa.UART2_RX, force=True)
fm.register(board_info.BUTTON_A, fm.fpioa.GPIO5, force=True)

uart_Port = UART(UART.UART2, 115200,8,0,0, timeout=1000, read_buf_len= 4096)

print(board_info.pin_map())

#M5StickV main button
main_button = GPIO(GPIO.GPIO5, GPIO.IN, GPIO.PULL_UP)

while True:
    img = sensor.snapshot()
    if main_button.value() == 0:
        lcd.display(img)
