#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define TXD2 17
#define RXD2 16
#define cntrl 21

BluetoothSerial SerialBT;

bool cntrlNow = LOW;
bool cntrlPast = LOW;
bool Reading = false;

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

  writeRegister(0x42, 0x12, 0x80, 22, 23, 100);  //Reset register
  delay(1000);
  writeRegister(0x42, 0x0C, 0x0C, 22, 23, 100);  //Enable Digital Zoom and Down Sampling
  writeRegister(0x42, 0x72, 0x22, 22, 23, 100);  //Set horizontal and vertical downsampling of 8
  writeRegister(0x42, 0x70, 0x3A, 22, 23, 100);  //Set Scaling XSC
  writeRegister(0x42, 0x71, 0x35, 22, 23, 100);  //Set Scaling YSC
  writeRegister(0x42, 0x73, 0xF2, 22, 23, 100);  //Set PCLK divide by 8
  writeRegister(0x42, 0xA2, 0x2A, 22, 23, 100);  //Scaling Delay lo cambiamos hace poquito, era 0x09  0x0c
  writeRegister(0x42, 0x11, 0x01, 22, 23, 100);  //Framerate CLKRC ~ 1.5fps
  writeRegister(0x42, 0x3E, 0x12, 22, 23, 100);

  writeRegister(0x42, 0x12, 0x04, 22, 23, 100); ///Allow RGB555 COM7
  writeRegister(0x42, 0x40, 0xF0, 22, 23, 100); ///RGB555 COM15




  SerialBT.begin("ESP32test"); //Bluetooth device name
  pinMode(cntrl,INPUT);

  delay(3000);

  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  DeleteSerial();
}

void loop(){
/*
  if(Serial2.available()>0){
    Serial.println(Serial2.read());
    }*/
  cntrlNow = digitalRead(cntrl);

  if (Reading && Serial2.available()){
      Serial.println(Serial2.read());
    }else if(cntrlNow == LOW && cntrlPast == HIGH){
      DeleteSerial();
      Serial.println("in");

      Reading = true;
    }else if(Reading && cntrlNow == HIGH && cntrlPast == LOW){
      Serial.println("end");
      Reading = false;
    }

    cntrlPast = cntrlNow;

}


void DeleteSerial(){
    while(Serial2.available()){
          Serial2.read();
        }
  }
