
void setup(){

  /*Before using the code make sure you have connected the following pins of the Camera:
    Camera SCL to Microcontroler SCL pin
    Camera SDA to Microcontroler SDA pin
    Camera RET to Logic High
    Camera PWDN to GND
    Camera 3V3 to 3,3 Volts
    Camera GND to GND
    Camera XLK to 10MHZ - 40MHz Clock
  */
  pinMode(5,OUTPUT);
  pinMode(19,OUTPUT);
  digitalWrite(5,HIGH);
  digitalWrite(19,HIGH);
  Serial.begin(9600);
   if(writeRegister(0x42, 0x12, 0x80, 5, 19, 500)){
        Serial.println("The register was succesfully overrote");
      }else{
        Serial.println("There was an error during the writing process");
        }
   Serial.print("Valor del registro: ");
   Serial.println(readRegister(0x43, 0x12, 5, 19, 500));
  }

void loop(){
  
  }
