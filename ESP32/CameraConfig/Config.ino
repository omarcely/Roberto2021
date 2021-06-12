
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
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(15,OUTPUT);

  digitalWrite(22,HIGH);
  digitalWrite(23,HIGH);
  digitalWrite(15,HIGH);
  Serial.begin(9600);

  //writeRegister(0x42, 0x12, 0x80, 22, 23, 100)  //Reset register

  writeRegister(0x42, 0x0C, 0x0C, 22, 23, 100)  //Enable Digital Zoom and Down Sampling
  writeRegister(0x42, 0x72, 0x33, 22, 23, 100)  //Set horizontal and vertical downsampling of 8
  writeRegister(0x42, 0x70, 0x28, 22, 23, 100)  //Set Scaling XSC
  writeRegister(0x42, 0x71, 0x28, 22, 23, 100)  //Set Scaling YSC
  writeRegister(0x42, 0x73, 0x03, 22, 23, 100)  //Set PCLK divide by 8
  writeRegister(0x42, 0xA2, 0x09, 22, 23, 100)  //Scaling Delay



  Serial.println(readRegister(0x43, 0x0C, 22, 23, 100));
  Serial.println(readRegister(0x43, 0x72, 22, 23, 100));
  Serial.println(readRegister(0x43, 0x70, 22, 23, 100));
  Serial.println(readRegister(0x43, 0x71, 22, 23, 100));
  Serial.println(readRegister(0x43, 0x73, 22, 23, 100));
  Serial.println(readRegister(0x43, 0xA2, 22, 23, 100));

  }

void loop(){

  }
