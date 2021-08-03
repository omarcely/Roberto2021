//UART communication
#define RXD2 16
#define TXD2 17

void setup() {
  
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,RXD2,TXD2);  
  
}

void loop() {
  if(Serial2.available()){
	Serial.println(Serial2.read());
  
  }     
}