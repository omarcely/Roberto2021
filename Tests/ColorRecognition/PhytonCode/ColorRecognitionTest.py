from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
import random
import serial
import time
import keyboard
from serial.serialutil import Timeout

count =0
try:
    ser = serial.Serial("COM9",115200)
    time.sleep(1)

    while True:
        if keyboard.is_pressed('w'):
            time.sleep(1)
            ser.write(b'g')
            count = 1
        if count == 1:
            count = 0
            hola=ser.readline() #if not detected any information in read serial, the program will not continue
            print(hola)
            if hola == b'1\r\n':
                print("rojo")
            if hola == b'2\r\n':
                print("verde")
            if hola == b'3\r\n':
                print("azul")
            if hola == b'4\r\n':
                print("nada")


        



except TimeoutError:
    print("Error de conexion")
finally:
    print("Hecho")
