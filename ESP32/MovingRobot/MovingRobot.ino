#include "BluetoothSerial.h"
#include <Ultrasonic.h>

//Ultrasonic
#define uts_1 34
#define uts_2 35
#define uts_3  32
#define trigger 33

//UART communication
#define RXD2 16
#define TXD2 17

//Output H-Bridge
#define EA 13
#define S1 12
#define S2 14

#define EB 25
#define S3 27
#define S4 26


int distance[3] = {0, 0, 0}; //distance[0] = uts_1 (Left); distance[1] = uts_2 (Front); distance[2] = uts_3 (Right);  
const size_t dataLength = sizeof(distance) / sizeof(distance[0]);
const int frequency = 30000; //PWM's frequency
const int resolution = 10; //Resoltion 10 bits (0-1023)  
int S[4] = {S1,S2,S3,S4}; // Outputs H-Bridge
int EN[2] = {EA, EB}; //Enable to each Motor
int maxspeed = 1000; int minspeed = 700;
int dutyCycle[2] = {maxspeed,maxspeed};
int xwidth = 10; 
boolean sendToPhy = false;
char r;
char state;


//Ultrasoncs 
Ultrasonic ultra1(trigger,uts_1);
Ultrasonic ultra2(trigger,uts_2);
Ultrasonic ultra3(trigger,uts_3);

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
  
  ledcSetup(0, frequency, resolution);
  ledcSetup(1, frequency, resolution);
  ledcAttachPin(EA, 0);
  ledcAttachPin(EB, 1); 

}

void loop() {

  Main();
  
}
