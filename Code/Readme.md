# Source code of the final implementation

## ArduinoCode

In the ArduinoCode folder you can find two arduino files for the ESP32 DEVKIT1 microcontroller. By uploading the _BrainBlock.ino_ file into the board and wiring everything correctly, the device's sotware should be ready.

## PythonCode

By running the _RoadConstruction.py_ your computer should be ready to receive data from the ESP32 through bluetooth (As long as the Computer and the microcontroller are paired).

## VerilogCode

All the _.v_ files should be uploaded as design files of a new Vivado project. _ZyboZ7.xdc_ defines the constraints for a implementation on a ZyboZ7 board. After the project synthesis, the hardware of the device should be ready.


In order to have the vehicle working, you should upload the SW and HW codes, put the vehicle inside the maze and finally run the python script in order for the vehicle to start moving. You can see the maze reconstruction with all geometrical figures in the turtle pop-up window.
