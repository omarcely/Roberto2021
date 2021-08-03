import keyboard
import tools_RoadConstruction

firstTurn = False
firstTime = True
lastDistance = 0
tools_RoadConstruction.start()

while True: 
     
    if keyboard.is_pressed("s"):
        tools_RoadConstruction.ser.write(b's')
        tools_RoadConstruction.turtle.bye()
        tools_RoadConstruction.start()
        
    else:

        (firstTurn, firstTime, lastDistance) = tools_RoadConstruction.makeRoad(lastDistance, firstTurn, firstTime)
