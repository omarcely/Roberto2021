import serial
import keyboard as k
import turtle
import time

ser = serial.Serial('COM7',115200, timeout = 0.2)
lastDistance = 0
state = 'f' 
firstTurn = True
lab = turtle.Turtle()
scr = turtle.Screen()

lab.penup()
lab.right(90)
lab.forward(200)
lab.rt(180)
lab.pendown()

def makeRoad(lastDistance, currentDistance,state):
    global firstTurn

    if state == 'r' and firstTurn == True:
        lab.rt(90)
        firstTurn = False
    elif state == 'l' and firstTurn == True:
        lab.lt(90)
        firstTurn = False
    else:
        s = lastDistance-currentDistance
        if s >= 1:
            firstTurn = True
            lab.forward(5*s)
        

def firstTime():
    ser.write(b'r')
    aux = ser.readline().decode()
    firstDistance = 0
    if aux != '':
        firstDistance = int(aux)
    return firstDistance

currentDistance = firstTime()

while True: 
    
    if k.is_pressed("s"):
        stop = True
        ser.write(b's')
        while stop == True:
            if k.is_pressed("r"):
                stop = False
                firstTime()
            else:
                stop = stop

    else:
        lastDistance = currentDistance
        aux = ser.readline().decode()
        
        if aux != '': 
            if aux[0] == 'r':
                state = 'r'
            elif aux[0] == 'l':
                state = 'l'
            else:
                state = 'f'
                currentDistance = int(aux)
            makeRoad(lastDistance, currentDistance, state)
            
