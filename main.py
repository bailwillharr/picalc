import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT) # row 1
GPIO.setup(23, GPIO.OUT) # row 2
GPIO.setup(24, GPIO.OUT) # row 3
GPIO.setup(25, GPIO.OUT) # row 4
GPIO.setup(12, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # column 1
GPIO.setup(16, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # column 2
GPIO.setup(20, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # column 3
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # column 4
GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_UP) # break button

keys = [['1', '2', '3', 'A'],
        ['4', '5', '6', 'B'],
        ['7', '8', '9', 'C'],
        ['*', '0', '#', 'Gae']]

def checkRow(rowPin):
    GPIO.output(18, False)
    GPIO.output(23, False)
    GPIO.output(24, False)
    GPIO.output(25, False)
    GPIO.output(rowPin, True)
    return [GPIO.input(12), GPIO.input(16), GPIO.input(20), GPIO.input(21)]

activeDebounce = False
#debounceKey = [0, 0]

while True:
    pressedKeys = [checkRow(18), checkRow(23), checkRow(24), checkRow(25)]
    if not GPIO.input(26):
        break

    if not activeDebounce:
        for x in range(4): # x == ROWS
            for y in range(4): # y == COLUMNS
                currentKey = pressedKeys[x][y]
                if currentKey:
                        activeDebounce = True
                        debounceKey = [x, y]
                        print(keys[x][y])
    else:
        if not pressedKeys[debounceKey[0]][debounceKey[1]]:
            activeDebounce = False
    if activeDebounce:
        time.sleep(0.1)

GPIO.cleanup()
