import turtle
import serial 
import time
import keyboard

ser = serial.Serial('COM7',115200)
    
def start():
    stop = True
    while stop:
        if keyboard.is_pressed("r"):
            ser.write(b'r')
            time.sleep(0.1)
            turtle.Turtle._screen = None
            turtle.TurtleScreen._RUNNING = True 
            time.sleep(0.5)
            turtle.lt(90)
            stop = False
            time.sleep(2)
        else: 
            stop = True

def makeRoad(lastDistance, firstTurn, firstTime):

    serialInput = ser.readline().decode()
    if serialInput != '':

        if serialInput[0] == 'r' and firstTurn:
            turtle.rt(90)
            return (False, False, 0)

        elif serialInput[0] == 'l' and firstTurn:
            turtle.lt(90)
            return (False, False, 0)

        elif serialInput[0] == 'x' and firstTime:
            turtle.penup()
            turtle.forward(20)
            turtle.pendown()
            turtle.dot(25, "red")
            turtle.penup()
            turtle.backward(20)
            turtle.pendown()
            ser.write(b'd')
            return (True , False, 0)

        elif serialInput[0] == 'g' and firstTime:
            turtle.penup()
            turtle.forward(10)
            turtle.pendown()
            turtle.rt(90)
            turtle.color("green")
            turtle.begin_fill()
            for i in range(3):
                turtle.forward(20)
                turtle.lt(120)
            turtle.end_fill()
            turtle.color("black")
            turtle.penup()
            turtle.lt(90)
            turtle.backward(10)
            turtle.pendown()
            ser.write(b'd')
            return (True,False, 0)

        elif serialInput[0] == 'b' and firstTime:
            
            turtle.penup()
            turtle.forward(10)
            turtle.pendown()
            turtle.rt(90)
            turtle.color("blue")
            turtle.begin_fill()
            for i in range(4):
                turtle.lt(90)
                turtle.forward(20)    
            turtle.end_fill()
            turtle.color("black")
            turtle.penup()
            turtle.lt(90)
            turtle.backward(10)
            turtle.pendown()
            ser.write(b'd')
            return (True,False, 0)
        
        elif serialInput[0] == 'n' and firstTime:
            turtle.penup()
            turtle.forward(10)
            turtle.pendown()
            turtle.begin_fill()
            for i in range(5):
                turtle.forward(20)
                turtle.rt(144)
            turtle.end_fill()
            turtle.penup()
            turtle.backward(10)
            turtle.pendown()
            ser.write(b'd')
            return (True,False, 0)

        else:
            currentDistance = float(serialInput)
            difference = int(lastDistance-currentDistance)
            if 3 > difference >= 1:
                turtle.forward(4*difference)
            return (False,True, currentDistance)
    
    
