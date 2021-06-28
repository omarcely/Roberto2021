from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
import random
import serial
import time
from serial.serialutil import Timeout

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


try:
    w=64 #width of the image
    h=48 #height of the image
    ser = serial.Serial("/dev/ttyUSB0",115200)
    time.sleep(1)
    firstArray = np.zeros((h,w,2),dtype=np.uint8)  #it is possible to convert into unsigned integer since the instantiation of the array
    pixels = np.zeros((h,w,3), dtype=np.uint8)
    counter = 0

    while True:
        lecture = ser.readline()
        print(lecture)
        if lecture == b'in\r\n': #if the iniciation bit has appear, now we can put the pixels into de array

            #firstbyte = ser.readline()
            counter = 1 #counter for indicate that the iniciation bit has already passed

            for i in range(h):
                for j in range(w):
                    for p in range(2):
                        firstArray[i][j][p] = ser.readline()
        if lecture == b'end\r\n':
            if counter == 1:
                ser.close()
                break
            else:
                pass

    print(firstArray)
    convertArray(firstArray,pixels,h,w) #convert RGB555 to RGB888 compatible with usual PIL fuctions
    print(pixels)
    # Use PIL to create an image from the  array of pixels
    new_image = Image.fromarray(pixels)
    # Convert the pixels into an array using numpy (if necessary)
    #array = np.array(pixels, dtype=np.uint8)
    #show the imagen using PIL
    plt.imshow(new_image, animated=True)
    plt.axis(False)
    plt.show()

except TimeoutError:
    print("Error de conexion")
finally:
    print("Hecho")
