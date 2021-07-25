import keyboard as k
import robert 

firstTurn = True
currentDistance = robert.star()

while True: 
     
    if k.is_pressed("s"):
        stop = True
        robert.ser.write(b's')
        while stop == True:
            if k.is_pressed("r"):
                stop = False
                currentDistance = robert.star()
            else:
                stop = stop

    else:

        lastDistance = currentDistance
        serialInput = robert.ser.readline().decode()
        state = robert.defineState(serialInput)
        
        if state == 'f':
            currentDistance = float(serialInput)

        firstTurn = robert.makeRoad(lastDistance, currentDistance,state,firstTurn)

