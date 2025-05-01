import sensor
import pyb
import time

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()


uart = pyb.UART(1, 115200)
uart.init(115200, bits=8)

BITE_START = 0xAB
DELAY = 100

red_led = pyb.LED(1)
green_led = pyb.LED(2)

def send_result(data):
    high_byte_id = (data.id() >> 8) & 0xFF
    low_byte_id = data.id() & 0xFF

    high_byte_cx = (data.cx() >> 8) & 0xFF
    low_byte_cx = data.cx() & 0xFF

    high_byte_cy = (data.cy() >> 8) & 0xFF
    low_byte_cy = data.cy() & 0xFF

    checksum = BITE_START ^ high_byte_id ^ low_byte_id ^ high_byte_cx ^ low_byte_cx ^ high_byte_cy ^ low_byte_cy

    byte_data = bytearray([BITE_START,
                            high_byte_id,
                            low_byte_id,
                            high_byte_cx,
                            low_byte_cx,
                            high_byte_cy,
                            low_byte_cy,
                            checksum      ])
    uart.write(byte_data)

def get_tags(sensor: sensor.Sensor):
    img = sensor.snapshot()
    tags = img.find_apriltags()

    if tags:
        for tag in tags:
            img.draw_rectangle(tag.rect, color=(255, 0, 0))
            img.draw_cross(tag.cx, tag.cy, color=(0, 255, 0))

            print(f"ID: {tag.id}")

    return tags

while True:
    clock.tick()

    markers = get_tags(sensor)

    if markers:
        send_result(markers[0])

        if int(markers[0].id) == 2:
            green_led.on()
        else:
            red_led.on()


    pyb.delay(DELAY)

    red_led.off()
    green_led.off()
