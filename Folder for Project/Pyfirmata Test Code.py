try:
    from pyfirmata import Arduino, util
except:
    import pip
    pip.main({"install", "pyfirmata"})
    from pyfirmata import Arduino, util

import time
import csv

board = Arduino("COM3")

iterator = util.Iterator(board)
iterator.start()

gas_sensor = board.get_pin("a:0:i")


counter = 0
maxvalue = 1

while counter <= maxvalue:
    time.sleep(0.01)
    print (gas_sensor.read()*100)
    counter += 1
    maxvalue += 1 