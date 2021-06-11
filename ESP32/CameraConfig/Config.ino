
void setup(){

  /*Before using the code make sure you have connected the following pins of the Camera:
    Camera SCL to Microcontroler SCL pin
    Camera SDA to Microcontroler SDA pin
    Camera RET to ESP32 Reset control pin
    Camera PWDN to GND
    Camera 3V3 to 3,3 Volts
    Camera GND to GND
    Camera XLK to 10MHZ - 40MHz Clock
  */
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  digitalWrite(22,HIGH);
  digitalWrite(23,HIGH);
  Serial.begin(9600);
   if(writeRegister(0x42, 0x12, 0x80, 22, 23, 500)){
        Serial.println("The register was succesfully overrote");
      }else{
        Serial.println("There was an error during the writing process");
        }
   Serial.print("Valor del registro: ");
   Serial.println(readRegister(0x43, 0x12, 22, 23, 500));
  }

void loop(){

  }
