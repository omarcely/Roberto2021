#include "BluetoothSerial.h"
#include <HCSR04.h>
//Ultrasonic
#define uts_1 34
#define uts_2 35
#define uts_3  32
#define trigger 33

//UART communication
#define RXD2 16
#define TXD2 17
#define cntrl 21

//Output H-Bridge
#define EA 25
#define S1 26
#define S2 27

#define EB 13
#define S3 14
#define S4 12


double distance[3] = {0, 0, 0}; //distance[0] = uts_1 (Left); distance[1] = uts_2 (Front); distance[2] = uts_3 (Right);  
HCSR04 hc(trigger,new int[3]{uts_1,uts_2,uts_3},3);
double correctDistance = 12;
double lastDistanceFront=50;
double frontdiff = 50;
double diff = 0;
int count = 0;
int S[4] = {S1,S2,S3,S4}; // Outputs H-Bridge
int EN[2] = {EA, EB}; //Enable to each Motor
int topSpeed = 905; int minimumSpeed = 900;
int topSpeedB = 900;
int dutyCycle[2] = {topSpeed, topSpeedB};
char r;
int lastTurn = 1; // -1 left, 1 right;
boolean sendToPhy = false;
boolean done = false;

double currentDistance = 0;

//Bluetooth
BluetoothSerial SerialBT;

void setup() {
  
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,RXD2,TXD2);  
  SerialBT.begin("ESP32");

  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S4, OUTPUT);
  pinMode(cntrl, OUTPUT);

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

  digitalWrite(S[0],HIGH);
  digitalWrite(S[1],LOW);
  digitalWrite(S[2],LOW);
  digitalWrite(S[3],HIGH); 

  ledcSetup(0, 4900, 10); //ledcSetup(chanel, frequency, resolution)
  ledcSetup(1, 4900, 10);
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
  if(SerialBT.available()){
      r = SerialBT.read();
      if(r == 'r'){
        sendToPhy = true;
      }else if(r == 's'){
        sendToPhy = false;
        count = 0;
      }else{
        sendToPhy = sendToPhy;
      }
  }
  if(sendToPhy){
        
      distance[0] = hc.dist(0);
      delay(5);
      distance[1] = hc.dist(1);
      delay(5); 
      distance[2] = hc.dist(2);
      delay(5);
      frontdiff = lastDistanceFront-distance[1];
      delayMicroseconds(5);
      lastDistanceFront = distance[1];
      if((distance[1]<20) &&(distance[1]!= 0) && (frontdiff < 25)){

          //The car has stopped and sends the control signal.
          dutyCycle[0] = 0;
          dutyCycle[1] = 0;
          ledcWrite(0,dutyCycle[1]);
          ledcWrite(1,dutyCycle[0]); 
          delay(4000);
          digitalWrite(cntrl,HIGH);
          delay(1000);
          digitalWrite(cntrl,LOW);

          //Read the answer from the FPGA, after it sends a char to Python.
          if(Serial2.available()){
              switch(Serial2.read()){
                  case 1: 
                    SerialBT.println('x');
                  break;
                  case 2: 
                    SerialBT.println('g');
                  break; 
                  case 3: 
                    SerialBT.println('b');
                  break; 
                  default: 
                    SerialBT.println('n');
                  break; 
              }
              delay(10);

              //The car wait for a control signal, after it could make the turn.
              done = false;
              while(done == false){
                  if(SerialBT.available()){
                      if(SerialBT.read() == 'd'){
                        done = true;
                      }
                  }
              }
          }

          //Make the turn.
          if((distance[0]<20) & (distance[2]<20)){
              dutyCycle[0] = topSpeed;
              dutyCycle[1] = topSpeedB;
              ledcWrite(0,dutyCycle[1]);
              ledcWrite(1,dutyCycle[0]); 
              lastTurn = lastTurn;
              delay(850); 
          }else if((distance[0]>=20) && (distance[0] > distance[2])){
              dutyCycle[0] = 0;
              dutyCycle[1] = topSpeedB+124;
              SerialBT.println('l');    
              ledcWrite(0,dutyCycle[1]);
              ledcWrite(1,dutyCycle[0]); 
              lastTurn = -1;
              delay(800);  
              distance[1] = hc.dist(1);
          }else{
              dutyCycle[0] = topSpeed+105;
              dutyCycle[1] = 0;
              SerialBT.println('r');  
              ledcWrite(0,dutyCycle[1]);
              ledcWrite(1,dutyCycle[0]); 
              lastTurn = 1;
              delay(820); 
              distance[1] = hc.dist(1);
          }


   
      }else if((distance[0]<50) || (distance[2]<50)){
      //Forward 
          SerialBT.println(distance[1]);
          if(lastTurn == -1){
            currentDistance = hc.dist(2);
            }else if(lastTurn == 1){
            currentDistance = hc.dist(0);
              }
          delayMicroseconds(10);
          diff = correctDistance - currentDistance;
          if((diff < 10)&&(diff > 0.5) && count == 80){
            dutyCycle[0] = topSpeed + (max(0,lastTurn)*50)+(min(0,lastTurn)*50);
            dutyCycle[1] = topSpeedB - (min(0,lastTurn)*40) - (max(0,lastTurn)*50);
            delay(1);
            ledcWrite(0,dutyCycle[1]);
            ledcWrite(1,dutyCycle[0]); 
            }else if((-10 < diff) &&(diff < -0.5) && count == 80){
              dutyCycle[0] = topSpeed - (min(0,lastTurn)*50) - (max(0,lastTurn)*50);
              dutyCycle[1] = topSpeedB + (max(0,lastTurn)*40) + (min(0,lastTurn)*50);
              delay(1);
              ledcWrite(0,dutyCycle[1]);
              ledcWrite(1,dutyCycle[0]); 
              }else{
                dutyCycle[0] = topSpeed;
                dutyCycle[1] = topSpeedB;
                delay(1);
                ledcWrite(0,dutyCycle[1]);
                ledcWrite(1,dutyCycle[0]); 
                if(count == 80){
                  count = count; 
                  }else{
                    count = count + 1;
                    }
                }
      }else{
          //Stop the car.
          dutyCycle[0] = 0;
          dutyCycle[1] = 0;
          ledcWrite(0,dutyCycle[1]);
          ledcWrite(1,dutyCycle[0]);
          delay(500);
      }
      
  }else{
      //Stop the process.
      dutyCycle[0] = 0;
      dutyCycle[1] = 0;
      ledcWrite(0,dutyCycle[1]);
      ledcWrite(1,dutyCycle[0]);
      delay(10);
  }
      
}
