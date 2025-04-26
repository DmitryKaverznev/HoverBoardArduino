import sensor, image
import pyb


sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.HD)


uart = pyb.UART(3, 115200)
uart.init(115200, bits=8)


BITE_START = 0xAB
DELAY = 1000

def send_result(data: int):
    byte = bytearray(BITE_START.value + data)
    uart.write(byte)


def find_aruco(sensor: sensor.Sensor):
    img = sensor.snapshot()

    markers = img.find_aruco_markers(
        family=image.ARUCO_DICT_4X4, 
        threshold=100
    )

    if markers:
        for marker in markers:
            print(f"ID: {marker.id()}, Rotation: {marker.rotation()}, Center: ({marker.cx()}, {marker.cy()})")
    
    return markers

while True:
    markers = find_aruco(sensor)
    
    if len(markers) != 0:
        send_result(markers[0].id())

    pyb.delay(DELAY)