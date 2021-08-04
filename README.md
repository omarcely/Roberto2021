# Self-Driving Maze Reconstructing Vehicle

## Description

This branch contains the source code and design files of a Maze Reconstructing Vehicle. This vehicle uses 3 HC-SR04 ultrasonic sensors in order to messure the distance of the vehicle relative to the maze walls and navigate throughout them. In addition, an OV7670 camera module allows the vehicle to identify the color of the geometrical figures located on some of the corners. The camera data is obtained and processed by a ZyboZ7 FPGA, while the navigation, distance messurements and Bluetooth communication with a PC is carried out by an ESP32 microcontroller.

The block diagram used during the design process was the following:

![Diagrama HW-SW](https://user-images.githubusercontent.com/43284148/128103636-0667f414-3cb7-49fc-acc7-628538e66948.png)




## General Considerations

As you might notice, this branch contains 4 folders: Code, ChasisDesign, GeneralInformation, Tests.

### Code

Contains the code used in the final implementation of the vehicle. This is the only folder requiered in order to replicate the device and have similar results.

### ChasisDesign 

Due to the huge size of the ZyboZ7, our team made a custom design of the vehicle's chassis in order to assemble all the components. The design files can be found on this folder.

### GeneralInformation

Has some PDFs with documentation about the OV7670 as well as a report in Spanish with a full description of all the design and test process.

### Tests

Some of the previous versions of source code were gathered together into this folder. Here you can find folders with the code for: 
<ul>
  <li> Reading and reconstructing an image from the camera in a python code. </li>
  <li> Reading an image and sending the color of the figure to a python script.</li>
  <li> Drawing a road on a Python script using test data from a microcontroller. </li>
  <li> Testing the UART modules of the FPGA with a microcontroller.</li>
</ul>

