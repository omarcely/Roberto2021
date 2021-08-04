# Tests Results
Here you can find the differents types of test, that we made along the development of the project. In each folder has the codes from Python, Arduino and Verilog, that we used. Futhermore, you can see the results too.

For each test, you need to create a new verilog project and upload the code to the FPGA _ZyboZ7_. Remeber to update the constrain file too. For uploading the rest of the codes you shouldn't have any problem. You just must set the serial port in Pyhton and it should be ready for running.

## Color Recognition
In this folder you can find the code for making the color recogniton with the camera OV7670. This result is given by the FPGA, that in general terms, look at each byte for the dominance of red, green or blue. That result is sended via UART to the ESP32 and here goes to Python, where you can see it within console.


## Image Capture
Here is the Arduino, Python and Verilog code, that we builded to see the OV7670's picture. Here the image is kept in the RAM module and then is sended via UART byte per byte to the microcontroller  ESP32. From there, the result goes to Python, where we used the Matplotlib library, that allow us to make the graphic from the information of each byte.  

## Road Construction

Here is the Arduino and Python code, that allow us to see the road from the information, send it by the microcontroller. This sended information is setting inside the Arduino code, for this reason, the road is the same.   


## UART Comunication
In this folder you can use the code for UART comunication between two microcontrollers. However, in this case we maded for connecting the FPGA and the ESP32. Here you can recive and send bytes inside the Serial Monitor in Arduino IDE. 
