from PIL import Image, ImageDraw
import matplotlib.pyplot as plt
import numpy as np
import random
import serial 
import time
from processing_py import *
from serial.serialutil import Timeout
import keyboard as k
import matplotlib.animation as animation

def convertArray(firstArray,pixels,h,w): #this function takes the bytes saved into the firstArray matrix and covert them into RGB888 compatible bytes for then be almacenated into pixels array
    for i in range(h):
        for j in range(w):
            aux = np.unpackbits(firstArray[i][j])
            zeroaux = np.zeros(3,dtype=int)
            Raux = np.packbits(np.concatenate((zeroaux,aux[1:6]),axis=0), bitorder='big') 
            Gaux = np.packbits(np.concatenate((zeroaux,aux[6:11]),axis=0), bitorder='big') 
            Baux = np.packbits(np.concatenate((zeroaux,aux[11:16]),axis=0), bitorder='big') 
            R = Raux*(255/31)
            G = Gaux*(255/31)
            B = Baux*(255/31)
            pixels[i][j][0]=R
            pixels[i][j][1]=G
            pixels[i][j][2]=B
    return pixels

w=64 #width of the image
h=48 #height of the image 
fig = plt.figure()
firstArray = np.zeros((h,w,2),dtype=np.uint8)  #it is possible to convert into unsigned integer since the instantiation of the array
pixels = np.zeros((h,w,3), dtype=np.uint8)
# Use PIL to create an image from the  array of pixels
new_image = Image.fromarray(pixels)
# Convert the pixels into an array using numpy (if necessary)
#array = np.array(pixels, dtype=np.uint8)
#show the imagen using PIL
im = plt.imshow(new_image, animated=True) 
plt.axis(False)

def updatefig(*arg):
    convertArray(firstArray,pixels,h,w) #convert RGB555 to RGB888 compatible with usual PIL fuctions
    im.set_data(Image.fromarray(pixels))
    return im,


try:
    ser = serial.Serial("COM3",115200)
    time.sleep(1)
    counter = 0
    while True:     
        lecture = ser.readline()
        print(lecture)
        if lecture == b'in\r\n': #if the iniciation bit has appear, now we can put the pixels into de array 
            counter = 1 #counter for indicate that the iniciation bit has already passed
            for i in range(h):
                for j in range(w):
                    for p in range(2): 
                        firstArray[i][j][p] = ser.readline()
        if lecture == b'end\r\n':
            if counter == 1:
                counter = 0
                ani = animation.FuncAnimation(fig, updatefig, interval=5, blit=True)
                plt.show()
            else:
                pass

except TimeoutError:
    print("Error de conexion")
finally:
    print("Hecho")

