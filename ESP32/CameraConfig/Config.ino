#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define TXD2 17
#define RXD2 16
#define cntrl 21

BluetoothSerial SerialBT;

bool control_in=false;
bool cntrlNow = HIGH;
bool cntrlPast = HIGH;

void setup() {
    /*Before using the code make sure you have connected the following pins of the Camera:
    Camera SCL to Microcontroler SCL pin
    Camera SDA to Microcontroler SDA pin
    Camera RET to Logic High
    Camera PWDN to GND
    Camera 3V3 to 3,3 Volts
    Camera GND to GND
    Camera XLK to 10MHZ - 40MHz Clock
  */
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(15,OUTPUT);

  digitalWrite(22,HIGH);
  digitalWrite(23,HIGH);
  digitalWrite(15,HIGH);
  Serial.begin(115200);

  //writeRegister(0x42, 0x12, 0x80, 22, 23, 100)  //Reset register

  writeRegister(0x42, 0x0C, 0x0C, 22, 23, 100);  //Enable Digital Zoom and Down Sampling
  writeRegister(0x42, 0x72, 0x33, 22, 23, 100);  //Set horizontal and vertical downsampling of 8
  writeRegister(0x42, 0x70, 0x28, 22, 23, 100);  //Set Scaling XSC
  writeRegister(0x42, 0x71, 0x28, 22, 23, 100); //Set Scaling YSC
  writeRegister(0x42, 0x73, 0x03, 22, 23, 100);  //Set PCLK divide by 8
  writeRegister(0x42, 0xA2, 0x09, 22, 23, 100);  //Scaling Delay
  writeRegister(0x42, 0x11, 0x9C, 22, 23, 100);  //Framerate CLKRC ~ 1.5fps


  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(cntrl,INPUT);

  delay(10000);
}

void loop(){
  cntrlNow = digitalRead(cntrl);
  if(cntrlNow == LOW && cntrlPast == HIGH){ //Only begin to read and print if the control pin has already indicated the begin of the frame

        Serial.println("in");

        for(int i=0;i<9216;i++){
          if(Serial2.available()){ //Send the information to python just if there is any available in serial port
            Serial.println(Serial2.read(), BIN);
          }
        }

        Serial.println("end");
  }

  cntrlPast = cntrlNow;
}
