#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define TXD2 17
#define RXD2 16
#define cntrl 21

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(cntrl,INPUT);
}

byte info[36];
int i=0;
bool control_in=false;

void loop(){
  if(digitalRead(cntrl) == LOW){ //Only begin to read and print if the control pin has already indicated the begin of the frame
      if(i==0){
        if(control_in==false){ //Control variable for only one print of "in"
        Serial.println("in");
        control_in=true;
        }
      }
      if(Serial2.available()){ //Send the information to python just if there is any available in serial port
        Serial.println(Serial2.read());
        i++;
      }
      if(i==36){
        i=0;
        Serial.println("end");
        control_in=false;
      }
  }
  delay(50);
}

