from PIL import Image, ImageDraw
import matplotlib.pyplot as plt
import numpy as np
import random
import serial 
import time
from processing_py import *
from serial.serialutil import Timeout
import keyboard as k



try:
    w=4 #width of the image
    h=3 #height of the image 
    ser = serial.Serial("COM4",115200)
    time.sleep(1)
    pixels = np.zeros((h,w,3),dtype=np.uint8)  #it is possible to convert into unsigned integer since the instantiation of the array
    counter = 0

    while True:     
        lecture = ser.readline()
        print(lecture)
        if lecture == b'in\r\n': #if the iniciation bit has appear, now we can put the pixels into de array 
            counter = 1 #counter for indicate that the iniciation bit has already passed
            for i in range(h):
                for j in range(w):
                    for p in range(3): 
                        pixels[i][j][p] = ser.readline()
        if lecture == b'end\r\n':
            if counter == 1:
                ser.close()
                break
            else:
                pass
        if k.is_pressed("ENTER"):
            ser.close()

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
    print("Error de conexiÃ³n")
finally:
    print("Hecho")
