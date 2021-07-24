import turtle
import serial 
import time

ser = serial.Serial('COM3',115200)
lab = turtle.Turtle()
scr = turtle.Screen()

#Set up the start position
lab.penup()
lab.right(90)
lab.forward(200)
lab.rt(180)
lab.pendown()
    
def star():
    
    ser.write(b'r')
    time.sleep(0.3)
    aux = ser.readline().decode()
    firstDistance = 0
    if aux != '' and aux[0] != 'l' and aux[0] != 'r' and aux[0] != 's':
        firstDistance = float(aux)
    return firstDistance

def defineState(serialInput):
    if serialInput != '':       
        if serialInput[0] == 'r':
            return 'r'
        elif serialInput[0] == 'l':
            return 'l'
        elif serialInput[0] == 'x': #x: red
            return 'x'
        elif serialInput[0] == 'g':
            return 'g'
        elif serialInput[0] == 'b':
            return 'b'
        else:
            return 'f'

def makeRoad(lastDistance, currentDistance, state, firstTurn):
    
    if state == 'r' and firstTurn:
        lab.rt(90)
        return False
    elif state == 'l' and firstTurn:
        lab.lt(90)
        return False
    elif state == 'x' and firstTurn:
        lab.penup()
        lab.forward(10)
        lab.pendown()
        lab.circle(20)
        lab.penup()
        lab.backward(10)
        lab.pendown()
        return False
    elif state == 'g' and firstTurn:
        lab.penup()
        lab.forward(10)
        lab.pendown()
        lab.rt(90)
        lab.forward(10)
        lab.lt(120)
        lab.forward(20)
        lab.lt(120)
        lab.forward(20)
        lab.lt(120)
        lab.forward(10)
        lab.penup()
        lab.lt(90)
        lab.backward(10)
        lab.pendown()
        return False
    elif state == 'b' and firstTurn:
        lab.penup()
        lab.forward(10)
        lab.pendown()
        lab.rt(90)
        lab.forward(10)
        lab.lt(90)
        lab.forward(20)
        lab.lt(90)
        lab.forward(20)
        lab.lt(90)
        lab.forward(20)
        lab.lt(90)
        lab.forward(10)
        lab.penup()
        lab.lt(90)
        lab.backward(10)
        lab.pendown()
        return False
    elif state == 'f':
        s = int(lastDistance-currentDistance)
        if 3 > s >= 1:
            lab.forward(4*s)
        return True
    return False
    
 