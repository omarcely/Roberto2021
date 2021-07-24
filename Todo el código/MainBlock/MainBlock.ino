#include "BluetoothSerial.h"

//Ultrasonic
#define uts_1 34
#define uts_2 35
#define uts_3  32
#define trigger 33

//UART communication
#define RXD2 16
#define TXD2 17

//Output H-Bridge
#define EA 25
#define S1 26
#define S2 27

#define EB 13
#define S3 14
#define S4 12


double distance[3] = {0, 0, 0}; //distance[0] = uts_1 (Left); distance[1] = uts_2 (Front); distance[2] = uts_3 (Right);  
int S[4] = {S1,S2,S3,S4}; // Outputs H-Bridge
int EN[2] = {EA, EB}; //Enable to each Motor
int topSpeed = 1021; int minimumSpeed = 900;
int dutyCycle[2] = {topSpeed, topSpeed};
int xwidth = 10; 
boolean sendToPhy = false;
boolean endCorrection = true;
boolean rightCorrection = false; 
char r;
char currentState, nextState;

//Bluetooth
BluetoothSerial SerialBT;

void setup() {
  
  Serial.begin(115200); 
  Serial2.begin(115200,SERIAL_8N1,RXD2,TXD2);  
  SerialBT.begin("ESP32test");

  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S4, OUTPUT);

  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(15,OUTPUT);

  pinMode(trigger,OUTPUT);
  pinMode(uts_1,INPUT);
  pinMode(uts_2,INPUT);
  pinMode(uts_3,INPUT);
  
  digitalWrite(22,HIGH);
  digitalWrite(23,HIGH);
  digitalWrite(15,HIGH);

  ledcSetup(0, 30000, 10); //ledcSetup(chanel, frequency, resolution)
  ledcSetup(1, 30000, 10);
  ledcAttachPin(EA, 0);
  ledcAttachPin(EB, 1); 
  
  writeRegister(0x42, 0x12, 0x80, 22, 23, 100);  //Reset register
  delay(1000);

  ///////////Set QQCIF resolution
  writeRegister(0x42, 0x0C, 0x0C, 22, 23, 100);  //Enable Digital Zoom and Down Sampling
  writeRegister(0x42, 0x72, 0x22, 22, 23, 100);  //Set horizontal and vertical downsampling
  writeRegister(0x42, 0x70, 0x3A, 22, 23, 100);  //Set Scaling XSC
  writeRegister(0x42, 0x71, 0x35, 22, 23, 100);  //Set Scaling YSC
  writeRegister(0x42, 0x73, 0xF2, 22, 23, 100);  //Set PCLK divide
  writeRegister(0x42, 0xA2, 0x2A, 22, 23, 100);  //Scaling Delay
  writeRegister(0x42, 0x11, 0x01, 22, 23, 100);  //Framerate CLKRC
  writeRegister(0x42, 0x3E, 0x12, 22, 23, 100);

  ///////////RGB 555
  writeRegister(0x42, 0x12, 0x04, 22, 23, 100); ///Allow RGB555 COM7
  writeRegister(0x42, 0x40, 0xF0, 22, 23, 100); ///RGB555 COM15

  //////////Color Matrix/
  writeRegister(0x42,0x4f, 0x80, 22, 23, 100);
  writeRegister(0x42,0x50, 0x80, 22, 23, 100);
  writeRegister(0x42,0x51, 0x00, 22, 23, 100);
  writeRegister(0x42,0x52, 0x22, 22, 23, 100);
  writeRegister(0x42,0x53, 0x5e, 22, 23, 100);
  writeRegister(0x42,0x54, 0x80, 22, 23, 100);
  writeRegister(0x42,0x55, 0x8F, 22, 23, 100);
  writeRegister(0x42,0x56, 0x40, 22, 23, 100);
  //writeRegister(0x42,0x57, 0x80, 22, 23, 100);
  writeRegister(0x42,0x58, 0x9e, 22, 23, 100);
  writeRegister(0x42,0x59, 0x88, 22, 23, 100);
  writeRegister(0x42,0x5a, 0x88, 22, 23, 100);
  writeRegister(0x42,0x5b, 0x44, 22, 23, 100);
  writeRegister(0x42,0x5c, 0x67, 22, 23, 100);
  writeRegister(0x42,0x5d, 0x49, 22, 23, 100);
  writeRegister(0x42,0x5e, 0x0e, 22, 23, 100);
  writeRegister(0x42,0x69, 0x00, 22, 23, 100);
  writeRegister(0x42,0x6a, 0x40, 22, 23, 100);
  writeRegister(0x42,0x6b, 0x0a, 22, 23, 100);
  writeRegister(0x42,0x6c, 0x0a, 22, 23, 100);
  writeRegister(0x42,0x6d, 0x55, 22, 23, 100);
  writeRegister(0x42,0x6e, 0x11, 22, 23, 100);
  writeRegister(0x42,0x6f, 0x9f, 22, 23, 100);
  writeRegister(0x42,0xb0, 0x84, 22, 23, 100);
  writeRegister(0x42,0xcF, 0x84, 22, 23, 100);
  ////Mirroring
  writeRegister(0x42,0x1E, 0x34, 22, 23, 100);

}

void loop() {
  brain();
  /*distance[0] = readUltrasonic(trigger,uts_1);
      delay(5);
      distance[1] = readUltrasonic(trigger,uts_2);
      delay(5); 
      distance[2] = readUltrasonic(trigger,uts_3);
      delay(5);
      Serial.print("Distancia iz: ");
      Serial.println(distance[0]);
      Serial.print("Distancia frente: ");
      Serial.println(distance[1]);
      Serial.print("Distancia der: ");
      Serial.println(distance[2]);
      delay(1000);*/
      
}
