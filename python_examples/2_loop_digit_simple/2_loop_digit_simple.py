# exixe modules: https://github.com/dekuNukem/exixe
# python library docs: https://github.com/dekuNukem/exixe/tree/master/python_library
# Demo 2: loop digits test
import exixe
import spidev
import time

spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz = 7800000
cs_pin = 16

my_tube = exixe.Exixe(cs_pin, spi)

# Update led to be purple & count from 0 -> 9 and reset back to 0 at 10
count = 0
while True:
    my_tube.set_led(127, 0, 127)  # Purple
    my_tube.set_digit(count)

    count = (count + 1) % 10
time.sleep(1)
