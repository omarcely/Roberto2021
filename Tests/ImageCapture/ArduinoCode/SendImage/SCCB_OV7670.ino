Skip to content
Search or jump to…

Pull requests
Issues
Marketplace
Explore
 
@felipeg86 
ocely
/
Roberto2021
1
01
Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights
Roberto2021/ESP32/CameraConfig/SCCB_OV7670.ino
@ocely
ocely Update SCCB_OV7670.ino
…
Latest commit 4d4934a 15 days ago
 History
 1 contributor
131 lines (97 sloc)  3.21 KB
  

byte readRegister(byte IdAdress, byte SubAdress, int SCL, int SDA, int Delay){
    byte Message[2] = {IdAdress-1,SubAdress};
    ////////////////Two Phases write Transmission///////////////////
    startTransmission(SCL, SDA, Delay);
    for (int phase = 1; phase <3; phase++){
          if (!writeByte(Message[phase - 1], SCL, SDA, Delay)){
            }
      }
     stopTransmission(SCL,SDA,Delay);
     ////////////////Two Phases read Transmission///////////////////
     startTransmission(SCL, SDA, Delay);
     writeByte(IdAdress, SCL, SDA, Delay);
     byte ReadedData = readByte(SCL, SDA, Delay);
     stopTransmission(SCL, SDA, Delay);
     return ReadedData;
  }




bool writeRegister(byte IdAdress, byte SubAdress, byte InputValue, int SCL, int SDA, int Delay){
     bool writingWasPerfect = true;
     byte Message[3] = {IdAdress,SubAdress, InputValue};
     startTransmission(SCL, SDA, Delay);
     for (int phase = 1; phase <4; phase++){
          if (!writeByte(Message[phase - 1], SCL, SDA, Delay)){
              writingWasPerfect = false;
            }
      }
      stopTransmission(SCL,SDA,Delay);
      return writingWasPerfect;
  }


void startTransmission(int SCL, int SDA, int Delay) //SCCB Start
{
  digitalWrite(SDA,HIGH);
  delayMicroseconds(Delay);

  digitalWrite(SCL,HIGH);
  delayMicroseconds(Delay);

  digitalWrite(SDA,LOW);
  delayMicroseconds(Delay);

  digitalWrite(SCL,LOW);
  delayMicroseconds(Delay);
}



bool writeByte(byte Data, int SCL, int SDA, int Delay){

  unsigned char CurrentBit;
  bool WasSuccessfullyWritten;

  for ( CurrentBit = 0; CurrentBit < 8; CurrentBit++ ) //Loop for sending each bit
  {
    if( (Data<<CurrentBit) & 0x80 )  //Check if the MSB of Data is 1 after the shifting
      digitalWrite(SDA,HIGH);
    else
      digitalWrite(SDA,LOW);

    delayMicroseconds(Delay);


  digitalWrite(SCL,HIGH);
  delayMicroseconds(Delay);

  digitalWrite(SCL,LOW);
  delayMicroseconds(Delay);
  }


  pinMode(SDA,INPUT); // Ready to read Don't care Bit
  digitalWrite(SDA,LOW); // Pull-up prevention
  delayMicroseconds(Delay);

  digitalWrite(SCL,HIGH);
  delayMicroseconds(Delay);

  WasSuccessfullyWritten = (digitalRead(SDA)==LOW);

  digitalWrite(SCL,LOW);
  delayMicroseconds(Delay);

  pinMode(SDA,OUTPUT);

  return WasSuccessfullyWritten ;
  }

byte readByte(int SCL, int SDA, int Delay){
    byte Register = 0x00;
    pinMode(SDA, INPUT);
    digitalWrite(SDA,LOW); // Pull-up prevention

    for (int CurrentBit = 0; CurrentBit <8; CurrentBit++){
          delayMicroseconds(Delay);

          digitalWrite(SCL,HIGH);
          delayMicroseconds(Delay);

          byte Current = (digitalRead(SDA)==HIGH)? 0x01:0x00;
          Register = Register | (Current<<(7-CurrentBit));

          digitalWrite(SCL,LOW);
          delayMicroseconds(Delay);
      }
  pinMode(SDA, OUTPUT);
  digitalWrite(SDA, HIGH);
  delayMicroseconds(Delay);
  digitalWrite(SCL,HIGH);
  delayMicroseconds(Delay);
  digitalWrite(SCL,LOW);
  delayMicroseconds(Delay);
  digitalWrite(SDA,LOW);
  return Register;
  }

void stopTransmission(int SCL, int SDA, int Delay) //SCCB Stop
{
  digitalWrite(SDA,LOW);
  delayMicroseconds(Delay);

  digitalWrite(SCL,HIGH);
  delayMicroseconds(Delay);

  digitalWrite(SDA,HIGH);
  delayMicroseconds(Delay);
}
© 2021 GitHub, Inc.
Terms
Privacy
Security
Status
Docs
Contact GitHub
Pricing
API
Training
Blog
About
Loading complete