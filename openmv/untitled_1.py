import pyb
import sensor

sensor.reset()

uart = pyb.UART(1, 115200)
uart.init(115200, bits=8)

BITE_START = 0xAB


def send_result(data: int):
    high_byte = (data >> 8) & 0xFF
    low_byte = data & 0xFF
    byte_data = bytearray([BITE_START, high_byte, low_byte])
    uart.write(byte_data)

while True:
    send_result(5)
